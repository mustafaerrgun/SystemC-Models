#include "bcd_decoder.h"

void bcd_decoder::decode() {
	// ############# COMPLETE THE FOLLOWING SECTION ############# //
    unsigned short n = val.read();
    if (n > 99) n %= 100;

    unsigned short tens = n / 10;
    unsigned short ones = n % 10;

    hi.write(static_cast<char>(tens)); // 0..9
    lo.write(static_cast<char>(ones)); // 0..9

	// ####################### UP TO HERE ####################### //
}
