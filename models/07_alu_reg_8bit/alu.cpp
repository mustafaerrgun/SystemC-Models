#include <iostream>
#include <iomanip>
#include "alu.h"
#include "tlm.h"
#include "systemc.h"

// to make things easier readable...
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;
using namespace std;

void alu::process_request() {

	tlm_generic_payload *payload;

    tlm_sync_enum tlm_resp;

    while(true){
        wait(r_peq.get_event());

        payload = r_peq.get_next_transaction();

        // Extract operands and opcode from payload
        unsigned char* ptr = payload->get_data_ptr();
        sc_uint<8> op_a = ptr[0];
        sc_uint<8> op_b = ptr[1];
        sc_uint<2> opcode = ptr[2];

        // Write to signals (connected to alu_functions)
        operand_a.write(op_a);
        operand_b.write(op_b);
        opcode_sig.write(opcode);

        wait(SC_ZERO_TIME); // Allow alu_functions to process

        // Read result from signal
        sc_uint<8> output = result.read();
        ptr[0] = output;
        payload->set_data_length(1); // Only result returned

        // Prepare backward call
        payload->set_response_status(TLM_OK_RESPONSE);
        tlm_phase phase = BEGIN_RESP;
        sc_time delay = SC_ZERO_TIME;

		// call nb_transport_bw
		tlm_resp = alu_socket->nb_transport_bw(*payload, phase, delay);
		if(tlm_resp != TLM_COMPLETED || phase != END_RESP)
		{
			cout << std::setw(9) << sc_time_stamp() << ": '" << name()
                    << "'\tprotocol error! "
                    << "nb_transport_bw call with phase!=END_RESP!" << endl;
            sc_stop(); 
		}
    }
}


// nb_transport_fw, implementation of fw calls from initiator
tlm_sync_enum alu::nb_transport_fw(
		tlm_generic_payload &payload,	// ref to Generic Payload
		tlm_phase &phase,				// ref to phase
		sc_time &delay_time				// ref to delay time
		)
{
    // check whether transaction is initiated correctly
	if(phase != BEGIN_REQ) {
		cout << std::setw(9) << sc_time_stamp() << ": '" << name()
				<< "'\tprotocol error! "
				<< "nb_transport_fw call with phase!=BEGIN_REQ!" << endl;
		sc_stop(); 
	}

    tlm_command cmd = payload.get_command();  
	int len = payload.get_data_length();

    if (len != 3) {
    // Handle error: unexpected payload size
        cout << "Error: Unexpected payload size: " << len << endl;
        payload.set_response_status(TLM_GENERIC_ERROR_RESPONSE);
        phase = END_REQ;
        return TLM_COMPLETED;
    }

    else if(cmd == TLM_READ_COMMAND) {
        // Use a fixed delay for each ALU operation (e.g., 50 ns for 3 bytes)
        delay_time += sc_time(50, SC_NS);

        // Put transaction into read payload event queue: the process_request() thread
        r_peq.notify(payload, delay_time);
        payload.set_response_status(TLM_OK_RESPONSE);
    }

    phase = END_REQ;
	return TLM_UPDATED;

}