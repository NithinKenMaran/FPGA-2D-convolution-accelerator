# 2D Convolution HLS Project — Usage Guide

This project implements a streaming 2D convolution accelerator using Vitis HLS, Vivado, and PYNQ-Z2.

The accelerator takes a 5×5 image, applies a 3×3 kernel, and produces a 7×7 full-convolution output. Image data is transferred using AXI DMA, while the kernel coefficients are loaded once through AXI-Lite registers before streaming.

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
│       └── unrolled.tcl
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

## 2. HLS Synthesis

Go to the HLS directory:

```bash
cd hls
```

Synthesize the baseline version:

```bash
make basic
```

Synthesize the pipelined version:

```bash
make pipelined
```

Synthesize the unrolled version:

```bash
make unrolled
```

To run all variants and print a summary:

```bash
./run_stream.sh
```

To read reports from already-generated builds:

```bash
./read_reports.sh
```

---

## 3. Example HLS Report Output

A typical output from `./read_reports.sh` may look like:

```text
==========================================
 HLS Synthesis Summary
==========================================
Variant      |    Latency |     Time(ns) |          DSP |       BRAM |         FF |        LUT
-------------+------------+--------------+--------------+------------+------------+-----------
basic        |       2832 |    2.832e+04 |       3 (1%) |          - |  1153 (1%) |  1446 (2%)
pipelined    |        246 |    2.460e+03 |     27 (12%) |          - |  4885 (4%) |  2151 (4%)
unrolled     |        246 |    2.460e+03 |     27 (12%) |          - |  4885 (4%) |  2151 (4%)
```

The `basic` version uses fewer resources but has much higher latency. The `pipelined` and `unrolled` versions are faster but use more DSPs.

---

## 4. Manual C++ Testbench

If Vitis HLS C simulation does not work on your system, run the testbench manually:

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

## 5. Vivado Block Design Generation

After synthesizing the desired HLS variant, run Vivado.

Example using the pipelined version:

```bash
cd hls
make pipelined

cd ../vivado
vivado -mode batch -source create_project.tcl
```

If successful, the generated files will be copied into `pynq/`:

```text
pynq/conv2d_design.bit
pynq/conv2d_design.hwh
```

These two files must have the same base name for PYNQ to load the overlay correctly.

---

## 6. PYNQ Usage

Upload the following files to the PYNQ board:

```text
conv2d_design.bit
conv2d_design.hwh
conv2d_lab.ipynb
```

Open `conv2d_lab.ipynb` in Jupyter on the PYNQ board and run the cells.

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

## 7. Input and Output Format

The accelerator expects:

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

The kernel coefficients are loaded through AXI-Lite registers before starting the accelerator.

---

## 8. Example PYNQ Output

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

Example output:

```text
Hardware output:
[[  -9  -26  -50  -74  -98  -62  -25]
 [ -48 -128 -215 -260 -305 -178  -70]
 [-120 -300 -474 -519 -564 -306 -115]
 [-210 -510 -789 -834 -879 -456 -165]
 [-300 -720 -1104 -1149 -1194 -606 -215]
 [-234 -542 -811 -836 -861 -412 -145]
 [-147 -334 -488 -503 -518 -236  -75]]
```

If the accelerator output matches the Python reference model, the notebook prints:

```text
PASS: hardware output matches Python reference
```

---

## 9. AXI Timer Example Output

The notebook also measures execution using the AXI Timer.

Example:

```text
--- AXI Timer Measurement ---
HW timer: 850 cycles = 8.500 us @ 100 MHz
```

The exact cycle count may vary depending on the Vivado design and DMA behavior.

---

## 10. Common Issues

### DMA receive hangs

Most likely cause: `TLAST` was not asserted correctly.

For this design, `TLAST` must be asserted on the 49th output word:

```cpp
out_pkt.last = (out_count == 48);
```

### Output is shifted or incorrect

Check that the kernel orientation matches the HLS implementation. The HLS design assumes the kernel is already in the sliding-window orientation. If mathematical convolution is desired, provide the already-flipped kernel.

### PYNQ cannot find IP block

Print available IPs:

```python
print(ol.ip_dict.keys())
```

Then update the notebook handle names if needed.

### Overlay does not load

Make sure these files have the same base name:

```text
conv2d_design.bit
conv2d_design.hwh
```

They should be in the same directory as the notebook.

---

## 11. Full Build Sequence

From the project root:

```bash
cd hls
make pipelined

cd ../vivado
vivado -mode batch -source create_project.tcl
```

Then upload these files to the PYNQ board:

```text
pynq/conv2d_design.bit
pynq/conv2d_design.hwh
pynq/conv2d_lab.ipynb
```

