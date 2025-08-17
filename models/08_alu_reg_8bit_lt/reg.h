#ifndef __REG_H__
#define __REG_H__


#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include <tlm_utils/tlm_quantumkeeper.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(reg)
{
    public:
        simple_initiator_socket<reg> reg_socket;
        sc_signal<sc_uint<8>> result_storage;
    private:

        // Quantum keeper for LT timing
        tlm_quantumkeeper qk;

        // event for communication between processes
        sc_event send_event;

        // Process to generate operands and opcode, and send to ALU
        void generate_and_send();
        void trigger_send();


    public:
        SC_CTOR(reg)
        : reg_socket("reg_socket")
        ,result_storage("result_storage")
        {
            SC_THREAD(generate_and_send);
            SC_THREAD(trigger_send);

            // Quantum keeper setup (LT temporal decoupling)
            qk.set_global_quantum(sc_time(100, SC_NS));  
            qk.reset();
        }

};

#endif // __REG_H__