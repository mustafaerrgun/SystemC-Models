# Data Generator & Policer Modules

## Overview
This project implements two SystemC modules:
- **data_gen**: Generates pseudo-random packet sizes and inter-arrival times for simulation.
- **policer**: Token bucket–based rate limiter that decides whether to forward or discard incoming packets.

The modules are connected in `main.cpp` to simulate packet flow and policing behavior.

## Files
- `main.cpp` — Instantiates and connects modules, runs simulation.
- `data_gen.h` / `data_gen.cpp` — Packet generator module.
- `policer.h` / `policer.cpp` — Token bucket policer module.

## How It Works
- **data_gen** seeds the random number generator for reproducible results and emits packets of size `64–1499` bytes.
- **policer** maintains a token count (`r_pol` bytes/µs, capped at `max`) and:
  - Passes packets if enough tokens are available (tokens reduced by packet size).
  - Drops packets otherwise (token count unchanged).
