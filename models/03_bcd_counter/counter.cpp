#include "counter.h"

void counter::count() {
	// ############# COMPLETE THE FOLLOWING SECTION ############# //
    cnt.write(0);

    while (true) {
        wait();  

        if (!rst_n.read()) {
           
            cnt_int = 0;
        } else {
            cnt_int = (cnt_int == 99) ? 0 : (unsigned short)(cnt_int + 1);
        }

        cnt.write(cnt_int);
    }

	// ####################### UP TO HERE ####################### //
}
