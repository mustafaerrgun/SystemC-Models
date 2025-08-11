#include <systemc.h>
#include "comparator.h"

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_signal<unsigned int> sig_a, sig_b;
    sc_signal<short int> sig_result;

    // Instantiate comparator
    comparator comp("comp");
    comp.input_a(sig_a);
    comp.input_b(sig_b);
    comp.comp_val(sig_result);

    // Create VCD waveform trace file
    sc_trace_file *tf = sc_create_vcd_trace_file("comparator_waveform");
    sc_trace(tf, sig_a, "a");
    sc_trace(tf, sig_b, "b");
    sc_trace(tf, sig_result, "result");

    // Apply test values
    std::cout << "Starting simulation..." << std::endl;

    sig_a.write(5); sig_b.write(3);
    sc_start(1, SC_NS);
    std::cout << "a=5, b=3 -> result=" << sig_result.read() << std::endl;

    sig_a.write(4); sig_b.write(4);
    sc_start(1, SC_NS);
    std::cout << "a=4, b=4 -> result=" << sig_result.read() << std::endl;

    sig_a.write(2); sig_b.write(7);
    sc_start(1, SC_NS);
    std::cout << "a=2, b=7 -> result=" << sig_result.read() << std::endl;

    // Close trace file
    sc_close_vcd_trace_file(tf);

    return 0;
}
