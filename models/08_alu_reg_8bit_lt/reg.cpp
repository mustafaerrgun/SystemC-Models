#include <iostream>
#include <iomanip>
#include <cstdlib>      // for rand()
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
    sc_time delay;
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

        // Send transaction to ALU (LT style)
        delay = SC_ZERO_TIME;                 // start from zero; 
        reg_socket->b_transport(*payload, delay);

        // check response
        if (payload->get_response_status() != TLM_OK_RESPONSE) {
            SC_REPORT_ERROR("/reg", "Target returned error response");
        } else {
            // Single-call convention: target overwrites data[0] with 8-bit result 
            result_byte = data[0];
            result_storage.write(result_byte);

            std::cout << std::setw(9) << sc_time_stamp()
                      << ": 'reg'  A=" << static_cast<unsigned>(op_a)
                      << " B=" << static_cast<unsigned>(op_b)
                      << " op=" << static_cast<unsigned>(opcode)
                      << " -> result=" << static_cast<unsigned>(result_byte)
                      << std::endl;
        }

        // Advance local time via quantum keeper
        qk.set(qk.get_local_time() + delay);
        if (qk.need_sync()) {
            qk.sync();
        }

        delete payload; 
    }
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

