#include <iostream>
#include <iomanip>
#include "reg.h"
#include "tlm.h"
#include "systemc.h"

// to make things easier readable...
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;
using namespace std;

void reg::generate_and_send(){

    tlm_generic_payload* payload;

    tlm_sync_enum tlm_resp;
    tlm_response_status tlm_stat;
    sc_time delay;
    tlm_phase phase;

    unsigned char *resp_ptr;
    sc_uint<8> result_byte;

    while (true) {
        wait(send_event); // Wait for trigger

        // Randomly generate operands and opcode
        uint8_t op_a = rand() % 256;          // 8-bit operand
        uint8_t op_b = rand() % 256;          // 8-bit operand
        uint8_t opcode = rand() % 4;          // 2-bit opcode: 0-3

        // Prepare payload
        unsigned char data[3];
        data[0] = op_a;
        data[1] = op_b;
        data[2] = opcode;

        payload = new tlm_generic_payload;
        payload->set_command(TLM_READ_COMMAND); 
        payload->set_data_ptr(data);
        payload->set_data_length(3);
        payload->set_response_status(TLM_INCOMPLETE_RESPONSE);

        // Send transaction to ALU
        delay = SC_ZERO_TIME;
        phase = BEGIN_REQ;
        tlm_resp = reg_socket->nb_transport_fw(*payload, phase, delay);

        // check response
		if(tlm_resp != TLM_UPDATED || phase != END_REQ) {
			cout << std::setw(9) << sc_time_stamp() << ": '" << name()
					<< "'\tprotocol error! "
					<< "Read request not completed appropriately!" << endl;
			sc_stop(); 
		}

        // now we wait for the response
		cout << std::setw(9) << sc_time_stamp() << ": '" << name()
				<< "'\twaiting until transaction is finished." << endl << endl;
		wait(response_event);


        // now response via nb_transport_bw has arrived
		// evaluate return status of transaction
		tlm_stat = payload->get_response_status();
		cout << std::setw(9) << sc_time_stamp() << ": '" << name()
				<< "'\ttransaction finished ";

		if(tlm_stat == TLM_OK_RESPONSE)
			cout << "successfully. ";
		else if(tlm_stat == TLM_BURST_ERROR_RESPONSE)
			cout << "not or only in part successfully. ";
		else {
			cout << "unsuccessfully with unhandled return status: "
					<< tlm_stat << endl;
			sc_stop(); 
		}

        resp_ptr = payload->get_data_ptr();
        result_byte = (resp_ptr != nullptr) ? resp_ptr[0] : 0;

        result_storage.write(result_byte);

        delete payload;

    }

}

// implementation of nb_transport_bw
tlm_sync_enum reg::nb_transport_bw(
		tlm_generic_payload &payload,	// ref to Generic Payload
		tlm_phase &phase,				// ref to phase
		sc_time &delay_time				// ref to delay time
		)
{

	if(phase == BEGIN_RESP) {
		cout << std::setw(9) << sc_time_stamp() << ": '" << name()
				<< "'\twrite confirmation coming." << endl << endl;
	}
	else {
		cout << std::setw(9) << sc_time_stamp() << ": '" << name()
				<< "'\tprotocol error! Write not confirmed correctly!" << endl;
		sc_stop(); 
	}

	// increase delay time by a value corresponding to transfer time of
	// confirmation, assumed to be 1 clock cycle with 20 ns cycle time
	delay_time += sc_time(20, SC_NS);

	// producer process should go on after time needed for the confirmation
	response_event.notify(delay_time);

	// finish the transaction (end of 2nd phase)
	phase = END_RESP;
	return TLM_COMPLETED;
}

void reg::trigger_send() {
    while (true) {
        wait(300, SC_NS);
        send_event.notify();
        wait(800, SC_NS);
        send_event.notify();
        wait(200, SC_NS);
        send_event.notify();
        wait(200, SC_NS);
        send_event.notify();
        wait(200, SC_NS);
        send_event.notify();
        wait(400, SC_NS);
        send_event.notify();
        wait(1000, SC_NS);
        send_event.notify();
        wait(1000, SC_NS);
        send_event.notify();
        wait(400, SC_NS);
        send_event.notify();
    }
}

