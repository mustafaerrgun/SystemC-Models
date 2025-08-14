#ifndef __REG_H__
#define __REG_H__


#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/peq_with_get.h"

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(reg)
{
    public:
        simple_initiator_socket<reg> reg_socket;
        sc_signal<sc_uint<8>> result_storage;
    private:

        // events for communication between processes
        sc_event send_event;
	    sc_event response_event;

        // Process to generate operands and opcode, and send to ALU
        void generate_and_send();
        void trigger_send();

    public:
        // nb_transport_bw() - Nonblocking Transport Backward path for requests,
        //					   to be called from FIFO
        tlm_sync_enum nb_transport_bw(
                tlm_generic_payload &payload,	// ref to payload
                tlm_phase &phase,				// ref to phase
                sc_time &delay_time				// ref to delay time
        );

    public:
        SC_CTOR(reg)
        : reg_socket("reg_socket")
        ,result_storage("result_storage")
        {
            reg_socket.register_nb_transport_bw(this, &reg::nb_transport_bw);
            SC_THREAD(generate_and_send);
            SC_THREAD(trigger_send);
        }

};

#endif // __REG_H__