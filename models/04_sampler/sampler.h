#include <systemc.h>
#include "counter.h"

SC_MODULE(sampler){
    // port declarations
    sc_in<bool> clk;
    sc_in<int> min_max, period;
    sc_in<char> val;
    sc_out<int> s_val, s_val_1, s_val_10, s_val_100;


    // internal signals
    sc_signal<bool> trigger;
    // member variables
    int min_val, max_val;

    // process and member function
    void sample_process();
    bool convert_bcd(int a);
    // pointers to submodules
    counter *cnt;

    SC_CTOR(sampler){
        cnt= new counter("counter");
        (*cnt).clock(clk);
        (*cnt).max_cnt(period);
        cnt->overflow(trigger);

        SC_METHOD(sample_process);
        sensitive << trigger.posedge_event();
        dont_initialize();

        min_val = 0;
        max_val = 0;
    }

};