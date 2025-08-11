#include "comparator.h"

void comparator::compare() {
    unsigned int a,b;
    a = input_a.read();
    b = input_b.read();
    if(a>b) comp_val.write(1);
    else if(a==b) comp_val.write(0);
    else comp_val.write(-1);
}