#ifndef __ALU
#define __ALU

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

#include "alu_functions.h"

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(alu){
    public:
        sc_signal<sc_uint<8>> operand_a, operand_b, result;
        sc_signal<sc_uint<2>> opcode_sig;

        simple_target_socket<alu> alu_socket;

    public:
	// Target interface for LT
    void b_transport(tlm_generic_payload& trans, sc_time& delay);

    alu_functions *alu_func;
    
    SC_CTOR(alu):
    alu_socket("alu_socket")
    {
        alu_func = new alu_functions("alu_func");
        alu_func->operand_a(operand_a);
        alu_func->operand_b(operand_b);
        alu_func->opcode(opcode_sig);
        alu_func->result(result);

        // Register b_transport with the target socket
        alu_socket.register_b_transport(this, &alu::b_transport);

    }
};

#endif // __ALU