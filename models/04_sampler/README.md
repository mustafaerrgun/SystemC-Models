# Sampler Module

Sampler samples val on a periodic counter overflow, tracks min/max, outputs a selected value via min_max, and exposes its BCD digits (0..999).

## Ports (sampler):

**Inputs**: clk (bool), period (int), min_max (int: -1=min, 0=raw, +1=max), val (char or sc_uint<8>).

**Outputs**: s_val, s_val_1, s_val_10, s_val_100 (ints; BCD digits are 0–9).

## Internal:
Uses a counter submodule (clock, max_cnt, overflow). overflow drives an internal trigger; sample_process is sensitive to trigger posedge.


