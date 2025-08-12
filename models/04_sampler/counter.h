#include <systemc.h>

SC_MODULE(counter) {
    // Ports
    sc_in<bool> clock;        
    sc_in<int>  max_cnt;      
    sc_out<bool> overflow;    

    // State
    int cnt;

    // Process
    void tick() {
        int m = max_cnt.read();
        if (m <= 1) m = 1; // guard: period >= 1

        // increment and check overflow
        if (cnt + 1 >= m) {
            cnt = 0;
            overflow.write(true);   // one-cycle pulse
        } else {
            cnt += 1;
            overflow.write(false);
        }
    }

    SC_CTOR(counter) : cnt(0) {
        SC_METHOD(tick);
        sensitive << clock.pos();
        dont_initialize();

        overflow.initialize(false);
    }
};
