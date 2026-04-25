# Lab 5: Streaming FIR Filter on Pynq

## IMPORTANT

The actual code for the filters has been removed here.  Only the IPs are provided, with which you should be able to build the bit file and test.  Leave the IP for the MMIO solution as it is, and replace the code for the streaming interface with your own design.  You may need to modify the BD to get it working - do a first synthesis using the present code, and then edit the block design directly in Vivado, unless you are comfortable with TCL scripting.

Also, you need to skip step 1 and step 2 for now since you are directly using the IPs provided.  Once you change the fir_stream implementation, you can resynthesize it as needed.

## Overview

Implement a 21-tap low-pass FIR filter with two interfaces:
- **MMIO (AXI-Lite)**: one sample per CPU round-trip (baseline)
- **DMA (AXI-Stream)**: bulk transfer, hardware processes autonomously

Compare throughput and explore how HLS directives (unroll, pipeline)
affect performance and resource usage.


## Directory Structure

```
hls/
  fir_common.h        Data type and coefficient definitions
  fir_coeffs.h        Generated filter coefficients
  fir_stream.h/cpp    Streaming FIR (AXI-Stream + DMA)
  fir_mmio.h/cpp      MMIO FIR (AXI-Lite, single-sample)
  fir_stream_tb.cpp   Testbench for streaming version
  fir_mmio_tb.cpp     Testbench for MMIO version
  Makefile            Simulation (system g++) and synthesis targets
  synth_stream.tcl    Vitis HLS synthesis + IP export (streaming)
  synth_mmio.tcl      Vitis HLS synthesis + IP export (MMIO)

vivado/
  create_project.tcl  Block design: PS + DMA + both FIR IPs + AXI Timer

pynq/
  fir_lab.ipynb       Jupyter notebook (run on Pynq board)
  fir_lab.py          Equivalent Python script
  fir_design.bit      (generated) Bitstream
  fir_design.hwh      (generated) Hardware handoff

generate_vectors.py   Generate coefficients and test vectors
input.txt             (generated) Test input signal
expected_output.txt   (generated) Reference output
```

## Build Flow

### Step 1: Generate test vectors and simulate

Requires `XILINX_HLS` environment variable (set by Vitis HLS setup).

```bash
cd hls
make sim          # generates vectors, compiles with system g++, runs both testbenches
```

### Step 2: HLS synthesis and IP export

```bash
make synth        # runs vitis_hls for both MMIO and streaming IPs
```

### Step 3: Vivado block design and bitstream

```bash
cd ../vivado
vivado -mode batch -source create_project.tcl
```

This creates the block design, runs synthesis and implementation,
and copies the bitstream and .hwh to `pynq/`.

### Step 4: Run on Pynq

Copy `pynq/fir_design.bit`, `pynq/fir_design.hwh`, and
`pynq/fir_lab.ipynb` to the Pynq board and run the notebook.

## Data Type Configuration

Edit `hls/fir_common.h` to switch between float and fixed-point:

```c
/* Choose one: */
#define USE_FLOAT
/* #define USE_FIXED */
```

When using `USE_FIXED`, adjust the `ap_fixed<W,I>` parameters and
update the Python side to use the matching data format.

## Things to Explore

1. **MMIO vs DMA speedup**: How much faster is DMA? Why?
2. **Unroll factor**: What happens when you remove `#pragma HLS UNROLL`
   from the MAC loop? How does II change?
3. **Resource limits**: With 21 taps fully unrolled, how many DSP48s
   are used? What is the maximum tap count that fits?
4. **Fixed-point**: Switch to `ap_fixed<16,4>`. How do resources and
   timing change? Is the filter output still correct?
5. **AXI Timer**: Compare Python timing with cycle-accurate HW timing.
   What is the overhead of the Python/DMA setup?

## Register Map Notes

After HLS synthesis, check the generated driver headers for exact
register offsets:
- `hls_fir_stream/sol1/impl/ip/drivers/*/src/xfir_stream_hw.h`
- `hls_fir_mmio/sol1/impl/ip/drivers/*/src/xfir_mmio_hw.h`

Update the Python code if offsets differ from the defaults used
in the notebook.
