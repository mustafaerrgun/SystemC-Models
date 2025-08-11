# SystemC Models

This repository contains example SystemC modules, starting from very simple to more advanced designs.

## ⚙ Requirements
To build and run the examples you will need:

* SystemC 2.3.3

* GTKWave (for viewing waveform .vcd files)

## 📂 Current Modules

|   | Module Name | 
|----|-------------|
| 01 | Comparator

## 🛠 How to Build & Run

Each module folder contains its own **Makefile**.

Navigate into the module’s folder and run:
```bash
cd 01_comparator
make
```
This will compile the source files in that folder and produce an executable, for example: **comparator.x**

After building, run:

```bash
./comparator.x
```

This generate a VCD waveform file in the same folder (e.g., comparator_waveform.vcd).