#ifndef __ALU
#define __ALU

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/peq_with_get.h"

#include "alu_functions.h"

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(alu){
    public:
        sc_signal<sc_uint<8>> operand_a, operand_b, result;
        sc_signal<sc_uint<2>> opcode_sig;

        simple_target_socket<alu> alu_socket;

    private:
        peq_with_get<tlm_generic_payload> r_peq;

        void process_request();

    public:
    // nb_transport_fw() - Nonblocking Transport Forward path for requests,
	//					   to be called from producer or consumer
	tlm_sync_enum nb_transport_fw(
			tlm_generic_payload &payload,	// ref to payload
			tlm_phase &phase,				// ref to phase
			sc_time &delay_time				// ref to delay time
	);

    alu_functions *alu_func;
    
    SC_CTOR(alu):
    alu_socket("alu_socket")
    , r_peq("r_peq")
    {
        alu_func = new alu_functions("alu_func");
        alu_func->operand_a(operand_a);
        alu_func->operand_b(operand_b);
        alu_func->opcode(opcode_sig);
        alu_func->result(result);

        alu_socket.register_nb_transport_fw(this, &alu::nb_transport_fw);

        SC_THREAD(process_request);
    }
};

#endif // __ALU