#include "systemc.h"

SC_MODULE(stim_gen) {
	sc_out<bool> clk;
    sc_out<int> period, msm;
    sc_out<char> val;

	void c_gen();

	SC_CTOR(stim_gen) {
		SC_THREAD(c_gen);
	}
};
