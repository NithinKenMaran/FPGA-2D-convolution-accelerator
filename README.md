# Streaming 2D Convolution Accelerator — Usage Guide

This project implements a streaming 2D convolution accelerator using Vitis HLS, Vivado, and PYNQ-Z2.

The accelerator accepts a 5×5 input image, applies a 3×3 kernel, and produces a 7×7 full-convolution output. Image pixels are transferred using AXI DMA, while the 3×3 kernel coefficients are loaded through AXI-Lite registers before streaming begins.

---

## 1. Project Layout

```text
.
├── hls/
│   ├── 2dconv.cpp
│   ├── 2dconv.h
│   ├── 2dconv_tb.cpp
│   ├── Makefile
│   ├── synth_stream.tcl
│   ├── run_stream.sh
│   ├── read_reports.sh
│   └── directives/
│       ├── basic.tcl
│       ├── pipelined.tcl
│       ├── unrolled.tcl
│       └── aggressive.tcl
│
├── vivado/
│   └── create_project.tcl
│
└── pynq/
    ├── conv2d_design.bit
    ├── conv2d_design.hwh
    └── conv2d_lab.ipynb
````

---

## 2. HLS Directive Sets

The project includes four HLS directive sets.

| Variant      | Purpose                                                                                                      |
| ------------ | ------------------------------------------------------------------------------------------------------------ |
| `basic`      | Disables automatic loop pipelining. Used as the low-resource, high-latency baseline.                         |
| `pipelined`  | Pipelines the main sliding-window and row-shift loops. This is the recommended implementation.               |
| `unrolled`   | Adds explicit unrolling of the 3×3 MAC loops. In this design, it may produce the same result as `pipelined`. |
| `aggressive` | Pipelines the outer image-row loop. This can reduce latency but may greatly increase resource usage.         |

The aggressive version is mainly for educational comparison.

---

## 3. Running HLS Synthesis

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
./run_stream.sh
```

Read reports from existing builds:

```bash
./read_reports.sh
```

---

## 4. Example HLS Report Output

Typical `./read_reports.sh` output:

```text
==========================================
 HLS Synthesis Summary
==========================================
Variant      |    Latency |     Time(ns) |          DSP |       BRAM |         FF |        LUT
-------------+------------+--------------+--------------+------------+------------+-----------
basic        |       2832 |    2.832e+04 |       3 (1%) |          - |  1153 (1%) |  1446 (2%)
pipelined    |        246 |    2.460e+03 |     27 (12%) |          - |  4885 (4%) |  2151 (4%)
unrolled     |        246 |    2.460e+03 |     27 (12%) |          - |  4885 (4%) |  2151 (4%)
aggressive   |        160 |    1.600e+03 |    177 (80%) |          - | 13624 (12%)|  6334 (11%)
```

The exact numbers may vary depending on code and HLS scheduling.

Interpretation:

* `basic` uses the fewest DSPs but has the highest latency.
* `pipelined` greatly reduces latency by increasing parallelism.
* `unrolled` may match `pipelined` because HLS already infers enough MAC parallelism to satisfy the pipelined loop.
* `aggressive` may reduce latency further but can consume a very large amount of DSP resources.

---

## 5. Manual C++ Testbench

If Vitis HLS C simulation fails on your Linux setup, run the testbench manually:

```bash
cd hls

env -u LD_LIBRARY_PATH \
PATH=/usr/bin:/bin \
/usr/bin/g++ -std=c++14 \
-I/tools/Xilinx/Vitis_HLS/2021.1/include \
2dconv.cpp 2dconv_tb.cpp \
-o 2dconv_tb_manual

./2dconv_tb_manual
```

Expected output:

```text
PASS: 2D convolution output and TLAST matched
```

---

## 6. Vivado Build

First synthesize the HLS IP variant you want to use.

Recommended:

```bash
cd hls
make pipelined
```

Then generate the Vivado block design and bitstream:

```bash
cd ../vivado
vivado -mode batch -source create_project.tcl
```

After a successful Vivado build, the following files should appear:

```text
pynq/conv2d_design.bit
pynq/conv2d_design.hwh
```

---

## 7. PYNQ Usage

Upload these files to the PYNQ board:

```text
conv2d_design.bit
conv2d_design.hwh
conv2d_lab.ipynb
```

Open `conv2d_lab.ipynb` in Jupyter and run the notebook.

The notebook loads the overlay:

```python
from pynq import Overlay

ol = Overlay("conv2d_design.bit")
```

Expected IP handles:

```python
dma = ol.axi_dma_0
conv2d = ol.conv2d_stream_0
hw_timer = ol.axi_timer_0
```

---

## 8. Input and Output Format

The design uses fixed dimensions:

```text
Input image:  5 × 5
Kernel:       3 × 3
Output image: 7 × 7
```

The DMA input buffer contains 35 words:

```text
25 real image pixels + 10 zero-padding pixels
```

The output buffer contains 49 words:

```text
7 × 7 output values
```

The output stream asserts `TLAST` on the 49th output word.

---

## 9. Example PYNQ Output

Example input image:

```text
[[ 1  2  3  4  5]
 [ 6  7  8  9 10]
 [11 12 13 14 15]
 [16 17 18 19 20]
 [21 22 23 24 25]]
```

Example kernel:

```text
[[-1 -2 -3]
 [-4 -5 -6]
 [-7 -8 -9]]
```

Example hardware output:

```text
[[  -9  -26  -50  -74  -98  -62  -25]
 [ -48 -128 -215 -260 -305 -178  -70]
 [-120 -300 -474 -519 -564 -306 -115]
 [-210 -510 -789 -834 -879 -456 -165]
 [-300 -720 -1104 -1149 -1194 -606 -215]
 [-234 -542 -811 -836 -861 -412 -145]
 [-147 -334 -488 -503 -518 -236  -75]]
```

Expected verification message:

```text
PASS: hardware output matches Python reference
```

---

## 10. Common Issues

### DMA receive hangs

Most likely cause: `TLAST` is missing or asserted at the wrong time.

For a 7×7 output, `TLAST` must be asserted on output index 48:

```cpp
out_pkt.last = (out_count == 48);
```

### Wrong output values

Check kernel orientation. The HLS implementation assumes the kernel is already in the orientation used by the sliding-window hardware. If mathematical convolution is desired, provide the already-flipped kernel.

### Overlay does not load

Make sure these files are in the same directory and have the same base name:

```text
conv2d_design.bit
conv2d_design.hwh
```

### PYNQ cannot find an IP block

Print available IP names:

```python
print(ol.ip_dict.keys())
```

Then update the notebook handle names accordingly.

---

## 11. Full Recommended Build Sequence

From the project root:

```bash
cd hls
make pipelined

cd ../vivado
vivado -mode batch -source create_project.tcl
```

Then upload to PYNQ:

```text
pynq/conv2d_design.bit
pynq/conv2d_design.hwh
pynq/conv2d_lab.ipynb
```

