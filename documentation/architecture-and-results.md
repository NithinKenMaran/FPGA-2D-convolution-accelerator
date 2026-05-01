# 2D Convolution Accelerator - EE5332 Course Project

**Author**: Nithin Ken Maran  
**Roll Number**: EE23B050

**Date**: April 2026

## Architecture

The 2D convolution accelerator is implemented using line buffers to store `K` rows of the image (where `K` is the dimension of the kernel), and a sliding window, that computes the dot product of the overlap between the kernel and the line buffer's contents.

An example architecture for a \(3 \times 3\) kernel and \(5 \times 5\) image is shown below:

![Kernel is implemented as a sliding window over the line buffer. A MAC loop iterates over the overlapping elements to produce the output pixel.](images/architecture/arch.jpg)

*Kernel is implemented as a sliding window over the line buffer. A MAC loop iterates over the overlapping elements to produce the output pixel.*

![When an image row gets filled, the line buffers are shifted up and the sliding window is reset to the left.](images/architecture/arch-reset.jpg)

*When an image row gets filled, the line buffers are shifted up and the sliding window is reset to the left.*

## Pareto Tradeoffs

The following is the output of my script: `read_reports.sh`, which compares the `csynth.rpt` files corresponding to 4 different directives:

- `basic`: Explicitly turn off loop pipelining and unrolling
- `Pipelined`: Pipeline all loops, and partition the line buffer arrays
- `Unroll`: Same as pipelined, but also unroll the MAC loop that computes dot product of kernel and overlapping line buffer elements
- `Aggressive`: Forces pipelining and unrolling of the outermost pixel processing loop

![Pareto plot](images/pareto/pareto.png)

### Tradeoffs

1. The `basic` version uses minimal resources, but has very high latency.
2. The `pipelined` and `unrolled` versions have much lower latency than `basic`, but use more resources.
3. The `aggressive` version has the least latency, but the DSP, FF and LUT count is much larger, and cannot fit on the Pynq-Z2 board.

## Measured Results

### Correctness

![Expected Output](images/result/expected-output.png)

*Expected Output*

<p align="center">
  <img src="images/result/hardware-output.png" width="40%" alt="Hardware Output">
  <img src="images/result/diff.png" width="55%" alt="Difference between expected and hardware output">
</p>

<p align="center">
  <em>Hardware Output</em> &nbsp;&nbsp;&nbsp;&nbsp; <em>Difference between expected and hardware output</em>
</p>

### Timing

![AXI Timer Output](images/result/hw-timer.png)

*AXI Timer Output*

![Comparison with SciPy](images/result/vs-scipy.png)

*Comparison with SciPy*

Since the hardware assumes the convolution kernel is pre-flipped before loading via AXI-Lite, we must use `correlate2d` from SciPy instead of `convolve2d`.

As seen above, the hardware accelerator gives a 1.94x speedup over the SciPy version running on ARM.
