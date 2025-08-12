#include <systemc.h>
#include <stim_gen.h>
#include <sampler.h>

int sc_main(int argc, char* argv[]){
    sc_signal<int> prd, msm;
    sc_signal<bool> clk;
    sc_signal<char> val;

    sc_signal<int>  s_val, s1, s10, s100;

    // Instantiate modules
    stim_gen stim("stim");
    stim.clk(clk);
    stim.period(prd);
    stim.msm(msm);     
    stim.val(val);

    sampler  dut ("sampler");
    dut.clk(clk);
    dut.period(prd);
    dut.val(val);
    dut.min_max(msm);  
    dut.s_val(s_val);
    dut.s_val_1(s1);
    dut.s_val_10(s10);
    dut.s_val_100(s100);

    // VCD tracing
    sc_trace_file* tf = sc_create_vcd_trace_file("sampler");
    sc_trace(tf, clk,   "clk");
    sc_trace(tf, prd,   "period");
    sc_trace(tf, msm,   "min_max");
    sc_trace(tf, val,   "val");
    sc_trace(tf, s_val, "s_val");
    sc_trace(tf, s1,    "s_val_1");
    sc_trace(tf, s10,   "s_val_10");
    sc_trace(tf, s100,  "s_val_100");

    // Run
    sc_start(1000, SC_NS);

    // Cleanup
    sc_close_vcd_trace_file(tf);

    return 0;

}