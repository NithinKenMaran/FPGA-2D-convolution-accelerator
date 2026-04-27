# Streaming 2D Convolution Accelerator — Usage Guide

This project implements a streaming 2D convolution accelerator using Vitis HLS, Vivado, and PYNQ-Z2.

The accelerator accepts a 64×64 input image, applies a 3×3 kernel, and produces a 66×66 full-convolution output. Image pixels are transferred using AXI DMA, while the 3×3 kernel coefficients are loaded through AXI-Lite registers before streaming begins.

---

## 1. Project Layout

```text
.
├── expected_output.txt
├── FPGA-tested-and-verified
│   └── conv2d.ipynb
├── generate_vectors.py
├── hls
│   ├── 2dconv_tb.cpp
│   ├── 2dconv.cpp
│   ├── 2dconv.h
│   ├── directives
│   │   ├── aggressive.tcl
│   │   ├── basic.tcl
│   │   ├── pipelined.tcl
│   │   └── unrolled.tcl
│   ├── hls_2dconv_stream_pipelined
│   │   ├── hls.app
│   │   └── sol1/
│   ├── Makefile
│   ├── read_reports.sh
│   ├── run_stream.sh
│   └── synth_stream.tcl
├── input.txt
├── pynq
│   ├── conv2d_design.bit
│   ├── conv2d_design.hwh
│   └── conv2d_lab_64x64.ipynb
├── README.md
└── vivado
    └── create_project.tcl
````

---

## 2. HLS Directive Sets

The project includes four HLS directive sets.

| Variant      | Purpose                                                                                                      |
| ------------ | ------------------------------------------------------------------------------------------------------------ |
| `basic`      | Disables automatic loop pipelining. This uses the lowest resources, but has high latency.|
| `pipelined`  | Pipelines the main sliding-window and row-shift loops. |
| `unrolled`   | Adds explicit unrolling of the 3×3 MAC loops.|
| `aggressive` | Pipelines the outer image-row loop. This reduces latency further, but uses far more DSPs.|

The aggressive version, for a 64x64 image, tries to achieve II=1 by unrolling all loops, but this exceeds the number of DSPs available on the PYNQ board, so this wasn't tested on hardware. For hardware testing, the `pipelined` version was used.
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
chmod +x run_stream.sh
./run_stream.sh
```

Read reports from existing builds:

```bash
chmod +x read_reports.sh
./read_reports.sh
```

---

## 4. Example HLS Report Output

Example `./read_reports.sh` output for a 64×64 image and 3×3 kernel:

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

## 5. Vivado Build

synthesize the intended HLS IP variant.

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

These files should then appear:

```text
pynq/conv2d_design.bit
pynq/conv2d_design.hwh
```

Upload these files to the PYNQ board along with the notebook.

---

## 6. PYNQ Usage

Upload these files to the PYNQ board:

```text
conv2d_design.bit
conv2d_design.hwh
conv2d_lab_64x64.ipynb
```

Open `conv2d.ipynb` in Jupyter and run the notebook.

---

## 7. Input and Output Format

The design uses fixed dimensions:

```text
Input image:  64 × 64
Kernel:       3 × 3
Output image: 66 × 66
```

The DMA input buffer contains 4224 words:

```text
4096 real image pixels + 128 zero-padding pixels
```

The 128 zero-padding pixels correspond to two additional zero rows of width 64.

The output buffer contains 4356 words:

```text
66 × 66 output values
```

The output stream asserts `TLAST` on the 4356th output word.

```cpp
out_pkt.last = (out_count == OUTPUT_STREAM_WORDS - 1);
```

---

## 8. Example PYNQ Output

Example input image preview:

```text
Top-left 5×5 of input image:
[[  1   2   3   4   5]
 [ 65  66  67  68  69]
 [129 130 131 132 133]
 [193 194 195 196 197]
 [257 258 259 260 261]]
```

Example kernel:

```text
[[-1 -2 -3]
 [-4 -5 -6]
 [-7 -8 -9]]
```

Example output preview:

```text
Hardware output shape:
(66, 66)

Top-left 8×8 of hardware output:
[[    -9    -26    -50    -74    -98   -122   -146   -170]
 [  -264   -620   -983  -1028  -1073  -1118  -1163  -1208]
 [  -840  -1896  -2910  -2955  -3000  -3045  -3090  -3135]
 [ -1800  -4104  -6366  -6411  -6456  -6501  -6546  -6591]
 [ -2760  -6312  -9822  -9867  -9912  -9957 -10002 -10047]
 [ -3720  -8520 -13278 -13323 -13368 -13413 -13458 -13503]
 [ -4680 -10728 -16734 -16779 -16824 -16869 -16914 -16959]
 [ -5640 -12936 -20190 -20235 -20280 -20325 -20370 -20415]]
```

Expected verification message:

```text
PASS: hardware output matches Python reference
```

---

## 9. Timing Example

Example board-level timing from the AXI Timer:

```text
HW timer: 190972 cycles = 1909.720 us @ 100 MHz
```

For a 66×66 output:

```text
Output pixels = 4356
Measured cycles = 190972
```

Board-level throughput:

```text
4356 / 190972 ≈ 0.0228 output pixels/cycle
```

Equivalent:

```text
≈ 43.8 cycles/output pixel
≈ 2.28 million output pixels/s at 100 MHz
```

Example comparison with SciPy:

```text
FPGA DMA+accelerator time: 1.909720 ms
SciPy correlate2d time:    2.379813 ms
FPGA speedup vs SciPy:     1.246x
```

The board-level timing includes DMA transfer, AXI interconnect, DDR access, stream handshaking, and transaction overhead. The HLS report latency is the core-only estimate.

---
