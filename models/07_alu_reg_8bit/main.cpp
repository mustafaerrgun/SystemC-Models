#include "alu.h"
#include "reg.h"
#include "systemc.h"

int sc_main(int argc, char *argv[]){


    reg register_file("Register_File");
	alu alu_unit("ALU_Unit");

    register_file.reg_socket.bind(alu_unit.alu_socket);

    // VCD tracing
    sc_trace_file* tf = sc_create_vcd_trace_file("alu_unit");
    sc_trace(tf, alu_unit.operand_a, "operand_a");
    sc_trace(tf, alu_unit.operand_b, "operand_b");
    sc_trace(tf, alu_unit.opcode_sig, "opcode");
    sc_trace(tf, alu_unit.result, "result");
    sc_trace(tf, register_file.result_storage, "result_from_reg");

    // simulation duration may be modified by command line parameter
	sc_time sim_dur = sc_time(5000, SC_NS);
	if(argc != 2) {
		cout << "Default simulation time = " << sim_dur << endl;
	}
	else {
		sim_dur = sc_time(atoi(argv[1]), SC_NS);
		cout << "Simulation time = " << sim_dur << endl;
	}

	// start simulation
	sc_start(sim_dur);

    
    sc_close_vcd_trace_file(tf);

	return (0);


}