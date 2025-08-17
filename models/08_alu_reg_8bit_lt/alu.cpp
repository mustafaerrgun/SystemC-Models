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


void alu::b_transport(tlm_generic_payload &payload, sc_time &delay) {
    unsigned char* data = payload.get_data_ptr();

    // Expect {A, B, opcode} in data[0..2]
    uint8_t op_a   = data[0];
    uint8_t op_b   = data[1];
    uint8_t opcode = data[2];

    // Drive signals for alu_functions
    operand_a.write(op_a);
    operand_b.write(op_b);
    opcode_sig.write(opcode);

    wait(SC_ZERO_TIME);   // allow combinational alu_functions to update

    // Get result
    uint8_t res = result.read();

    // Return result in same buffer (overwrite data[0], shrink length to 1)
    data[0] = res;
    payload.set_data_length(1);

    // Annotate compute delay
    delay += sc_time(50, SC_NS);

    // Response
    payload.set_response_status(TLM_OK_RESPONSE);
}