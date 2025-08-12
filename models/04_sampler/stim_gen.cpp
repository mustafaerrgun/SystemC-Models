#include "stim_gen.h"

void stim_gen::c_gen() {
    // Initialize outputs
    clk.write(false);
    period.write(10);  
    msm.write(0);      
    val.write(50);     

    wait(1, SC_NS);    

    sc_time half(5, SC_NS);
    while (true) {
        // clock: 10 ns period
        clk.write(true);
        wait(half);
        clk.write(false);
        wait(half);

        static int t = 0; t++;
        if (t == 20) { val.write(120); }
        if (t == 40) { msm.write(+1); }   // choose max
        if (t == 60) { msm.write(-1); }   // choose min
        if (t == 80) { msm.write(0); }    // back to raw
        if (t == 100){ period.write(5); } // speed up counter overflow
    }
}


