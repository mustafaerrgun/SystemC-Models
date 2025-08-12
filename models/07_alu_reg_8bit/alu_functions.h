#ifndef __ALU_FUNCTIONS
#define __ALU_FUNCTIONS

#include <systemc.h>

SC_MODULE(alu_functions){
    // 8-bit Ports
    sc_in<sc_uint<8>> operand_a;        
    sc_in<sc_uint<8>> operand_b;      
    sc_out<sc_uint<8>> result;

    // Operation selector
    sc_in<sc_uint<2>> opcode; // 2 bits: 00=add, 01=sub, 10=and, 11=or

    void do_operation() {
        switch(opcode.read()) {
            case 0: // ADD
                result.write(operand_a.read() + operand_b.read());
                break;
            case 1: // SUB
                result.write(operand_a.read() - operand_b.read());
                break;
            case 2: // AND
                result.write(operand_a.read() & operand_b.read());
                break;
            case 3: // OR
                result.write(operand_a.read() | operand_b.read());
                break;
            default:
                result.write(0);
                break;
        }
    }
    
    // Constructor
    SC_CTOR(alu_functions){
        SC_METHOD(do_operation);
        sensitive << operand_a << operand_b << opcode;
        dont_initialize(); // Do not initialize on startup

    }
};

#endif // __ALU_FUNCTIONS