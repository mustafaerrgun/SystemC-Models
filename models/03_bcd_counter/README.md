# BCD Decoder (0–99 Counter)
A simple SystemC design that counts from 0 to 99 and converts the value to BCD digits.
bcd_decoder outputs ASCII tens (hi) and ones (lo) characters.

## Files
counter.h/.cpp — rising-edge counter, async active-low reset, wraps at 99.

bcd_decoder.h/.cpp — converts val (0–99) to ASCII digits on hi (tens) and lo (ones).

main.cpp — instantiates modules and writes a bcd_counter.vcd trace.

