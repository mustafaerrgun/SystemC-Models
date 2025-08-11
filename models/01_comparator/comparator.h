#include "systemc.h"

SC_MODULE (comparator){
    // ports declaration
    sc_in<unsigned int> input_a;
    sc_in<unsigned int> input_b;
    sc_out<short int> comp_val;

    // processes
    void compare();

    //constructor
    SC_CTOR(comparator){
        SC_METHOD(compare);
        sensitive << input_a;
        sensitive << input_b;
    }
};