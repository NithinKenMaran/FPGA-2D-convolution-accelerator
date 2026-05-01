# Streaming 2D Convolution Accelerator

This project implements a streaming 2D image convolution accelerator using Vitis HLS, Vivado, and the PYNQ-Z2 FPGA.

The accelerator accepts a 64×64 input image, applies a 3×3 kernel, and produces a 66×66 full-convolution output. Image pixels are transferred using AXI DMA, and the 3×3 kernel coefficients are pre-loaded through AXI-Lite registers.

The input image is streamed in, pixel-by-pixel. The output image starts streaming as soon as the first input image is received. This accelerator achieves a 1.94x speedup over SciPy's `correlate2d` function running on an ARM processor.

The architecture, design tradeoffs, accuracy and timing measurement results are present in `./documentation/architecture-and-results.pdf`.

---

## Project Layout

```text
├── documentation
│   └── architecture-and-results.pdf
├── hls
│   ├── 2dconv_tb.cpp
│   ├── 2dconv.cpp
│   ├── 2dconv.h
│   ├── directives
│   │   ├── aggressive.tcl
│   │   ├── basic.tcl
│   │   ├── pipelined.tcl
│   │   └── unrolled.tcl
│   ├── hls_2dconv_stream_aggressive
│   │   ├── hls.app
│   │   └── sol1
│   ├── hls_2dconv_stream_basic
│   │   ├── hls.app
│   │   └── sol1
│   ├── hls_2dconv_stream_pipelined
│   │   ├── hls.app
│   │   └── sol1
│   ├── hls_2dconv_stream_unrolled
│   │   ├── hls.app
│   │   └── sol1
│   ├── Makefile
│   ├── read_reports.sh
│   ├── run_stream.sh
│   └── synth_stream.tcl
├── pynq
│   ├── conv2d_design.bit
│   ├── conv2d_design.hwh
│   └── conv2d-ap-fixed.ipynb
├── README.md
└── vivado
    └── create_project.tcl
```

`./hls_2dconv_stream_aggressive <or basic/pipelined/unrolled>` are HLS synthesis outputs. These folders contain the csynth reports for the respective set of directives.


## HLS Directive Sets


| Variant      | Purpose                                                                                                      |
| ------------ | ------------------------------------------------------------------------------------------------------------ |
| `basic`      | Disables automatic loop pipelining. This uses the lowest resources, but has high latency.|
| `pipelined`  | Pipelines the main sliding-window and row-shift loops. |
| `unrolled`   | Explicitly unrolls the 3×3 MAC loops.|
| `aggressive` | Pipelines the outer image-row loop. This reduces latency further, but uses far more DSPs, FFs and LUTs.|

The `aggressive` version, for a 64x64 image, tries to achieve II=1 by unrolling all loops, but this exceeds the number of DSPs available on the PYNQ board, so this wasn't tested on hardware. 
For hardware testing, the `pipelined` version was used.

---

## Reading Csynth Reports

I have included the HLS build files for all 4 variants. To make viewing the results easy, run my `read_reports` script:

```bash
chmod +x ./read_reports.sh
./read_reports.sh
```

This script reads the `csynth.rpt` files of the 4 pareto varients, and prints it in a readable format.


```text
==========================================
 HLS Synthesis Summary
==========================================
Variant      |    Latency |     Time(ns) |          DSP |       BRAM |         FF |        LUT
-------------+------------+--------------+--------------+------------+------------+-----------
basic        |     244614 |    2.446e+06 |       3 (1%) |    2 (~0%) |  1140 (1%) |  1458 (2%)
pipelined    |       9981 |    9.981e+04 |     27 (12%) |    14 (5%) |  3297 (3%) |  2148 (4%)
unrolled     |       9981 |    9.981e+04 |     27 (12%) |    14 (5%) |  3297 (3%) |  2148 (4%)
aggressive   |       4756 |    4.756e+04 |   759 (345%) |     6 (2%) | 63707 (59%) | 32135 (60%)
```

Interpretation:

* `basic` uses the fewest DSPs but has the highest latency.
* `pipelined` greatly reduces latency by increasing parallelism.
* `unrolled` may match `pipelined` because HLS already infers enough MAC parallelism to satisfy the pipelined loop.
* `aggressive` reduces latency further, but exceeds the available DSP resources on the PYNQ-Z2.

---

## Running HLS Synthesis

Go to the HLS directory:

```bash
cd hls
```

Synthesize one variant:

```bash
make basic
make pipelined
make unrolled
make aggressive
```

Run all variants and print a report summary:

```bash
chmod +x run_stream.sh
./run_stream.sh
```

Read reports from existing builds:

```bash
chmod +x read_reports.sh
./read_reports.sh
```

---

## Vivado Build

The `aggressive` variant offers the least latency, but cannot fit on the Pynq-Z2 board. The `pipelined/unrolled` variants are the next best option.

```bash
cd hls
make pipelined
```

Then generate the Vivado block design and bitstream:

```bash
cd ../vivado
vivado -mode batch -source create_project.tcl
```

These files should then appear:

```text
pynq/conv2d_design.bit
pynq/conv2d_design.hwh
```

Upload these files to the PYNQ board along with the notebook.

---

## PYNQ Usage

Upload these files to the PYNQ board:

```text
conv2d_design.bit
conv2d_design.hwh
conv2d_lab_64x64.ipynb
```

Open `conv2d.ipynb` in Jupyter and run the notebook.

---

## Results

The accuracy and timing results are documented in my project report: `./documentation/architecture-and-results.pdf`