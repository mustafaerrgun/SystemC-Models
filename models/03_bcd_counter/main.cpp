#include "stimulus.h"
#include "counter.h"
#include "bcd_decoder.h"

int sc_main(int argc, char *argv[]) {

	sc_signal<bool> clock, reset_n;
	sc_signal<unsigned short int> count_val;
	sc_signal<char> v_hi, v_lo;

	// ############# COMPLETE THE FOLLOWING SECTION ############# //

    stimulus stim("stimulus");
    stim.clk(clock);
    stim.rst_n(reset_n);


    counter cnt("counter");
    cnt.clk(clock);
    cnt.rst_n(reset_n);
    cnt.cnt(count_val);


    bcd_decoder bcd_dec("bcd_decoder");
    bcd_dec.val(count_val);
    bcd_dec.hi(v_hi);
    bcd_dec.lo(v_lo);


    sc_trace_file *tf = sc_create_vcd_trace_file("bcd_counter");
    sc_trace(tf, clock, "clock");
    sc_trace(tf, reset_n, "reset");
    sc_trace(tf, count_val, "counter_value");
    sc_trace(tf, v_hi, "High");
    sc_trace(tf, v_lo, "Low");

	// ####################### UP TO HERE ####################### //

	int n_cycles;
	if(argc != 2) {
		cout << "default n_cycles = 2000" << endl;
		n_cycles = 2000;
	}
	else {
		n_cycles = atoi(argv[1]);
		cout << "n_cycles = " << n_cycles << endl;
	}

	sc_start(n_cycles, SC_NS);

	sc_close_vcd_trace_file(tf);

	return 0;
}
