"""
Lab 5: FIR Filter -- MMIO vs DMA Streaming Comparison
=====================================================

Run on the Pynq board after loading fir_design.bit.
Demonstrates:
  1. MMIO-based FIR (one sample per PS-PL round-trip)
  2. DMA-based streaming FIR (bulk transfer, HW processes autonomously)
  3. Timing comparison
  4. AXI Timer for cycle-accurate HW measurement
"""

import time
import struct
import numpy as np
from pynq import Overlay, allocate

# ----------------------------------------------------------------
# 1. Load overlay
# ----------------------------------------------------------------
ol = Overlay("fir_design.bit")
print("Overlay loaded successfully")
print(f"IP blocks: {ol.ip_dict.keys()}")

# Grab IP handles
dma         = ol.axi_dma_0
fir_stream  = ol.fir_stream_0
fir_mmio_ip = ol.fir_mmio_0
hw_timer    = ol.axi_timer_0

# ----------------------------------------------------------------
# 2. Prepare test data
# ----------------------------------------------------------------
N_SAMPLES = 256
FS = 1000.0
t = np.arange(N_SAMPLES) / FS
# 50 Hz passband + 300 Hz stopband
x = (0.7 * np.sin(2 * np.pi * 50.0 * t) +
     0.3 * np.sin(2 * np.pi * 300.0 * t)).astype(np.float32)
x[0] += 1.0

# ----------------------------------------------------------------
# 3. MMIO FIR -- one sample at a time
# ----------------------------------------------------------------
# Discover register offsets from the HLS driver:
#   0x00 : Control (bit 0 = ap_start, bit 1 = ap_done)
#   0x10 : x_in
#   0x18 : return value (ap_return)
# These offsets come from the Vitis HLS synthesis report.

CTRL_REG    = 0x00
X_IN_REG    = 0x10      # check synthesis report for exact offset
AP_RETURN   = 0x10      # return value register (may overlap; check report)

# NOTE: The exact register map depends on the HLS synthesis output.
# Read the s_axi_control address map from the generated driver files:
#   hls_fir_mmio/sol1/impl/ip/drivers/fir_mmio_v1_0/src/xfir_mmio_hw.h
#
# Typical layout for: data_t fir_mmio(data_t x_in)
#   0x00  control     (ap_start=bit0, ap_done=bit1, ap_idle=bit2)
#   0x10  x_in        (32-bit float, written as unsigned)
#   0x20  ap_return   (32-bit float, read as unsigned)
#
# Adjust offsets below after checking the generated header.

X_IN_OFFSET    = 0x18
RETURN_OFFSET  = 0x10

def float_to_uint(f):
    return struct.unpack('<I', struct.pack('<f', f))[0]

def uint_to_float(u):
    return struct.unpack('<f', struct.pack('<I', u & 0xFFFFFFFF))[0]

def mmio_fir_one_sample(ip, x_val):
    """Send one sample through the MMIO FIR and read the result."""
    ip.write(X_IN_OFFSET, float_to_uint(x_val))
    ip.write(CTRL_REG, 0x01)          # ap_start
    while (ip.read(CTRL_REG) & 0x02) == 0:   # wait ap_done
        pass
    return uint_to_float(ip.read(RETURN_OFFSET))

print("\n--- MMIO FIR ---")
y_mmio = np.zeros(N_SAMPLES, dtype=np.float32)

t_start = time.perf_counter()
for i in range(N_SAMPLES):
    y_mmio[i] = mmio_fir_one_sample(fir_mmio_ip, float(x[i]))
t_mmio = time.perf_counter() - t_start

print(f"MMIO: {N_SAMPLES} samples in {t_mmio*1e3:.2f} ms "
      f"({t_mmio/N_SAMPLES*1e6:.1f} us/sample)")

# ----------------------------------------------------------------
# 4. DMA Streaming FIR
# ----------------------------------------------------------------
print("\n--- DMA Streaming FIR ---")

# Allocate contiguous buffers for DMA
in_buf  = allocate(shape=(N_SAMPLES,), dtype=np.float32)
out_buf = allocate(shape=(N_SAMPLES,), dtype=np.float32)

np.copyto(in_buf, x)
out_buf[:] = 0

# Tell the streaming FIR how many samples to process
fir_stream.write(0x10, N_SAMPLES)   # 'n' register (check report)
fir_stream.write(0x00, 0x01)        # ap_start

t_start = time.perf_counter()

# Start DMA transfers
dma.sendchannel.transfer(in_buf)
dma.recvchannel.transfer(out_buf)

# Wait for completion
dma.sendchannel.wait()
dma.recvchannel.wait()

t_dma = time.perf_counter() - t_start

y_dma = np.array(out_buf, dtype=np.float32)
print(f"DMA:  {N_SAMPLES} samples in {t_dma*1e3:.2f} ms "
      f"({t_dma/N_SAMPLES*1e6:.1f} us/sample)")

# ----------------------------------------------------------------
# 5. AXI Timer usage (optional, for cycle-accurate measurement)
# ----------------------------------------------------------------
# AXI Timer register map (from pg079):
#   0x00 TCSR0 : control/status
#   0x04 TLR0  : load register
#   0x08 TCR0  : counter register
#
# To measure elapsed cycles:
#   1. Load counter with 0
#   2. Start counting up
#   3. Do work
#   4. Read counter -> elapsed cycles at FCLK frequency

TCSR0 = 0x00
TLR0  = 0x04
TCR0  = 0x08

def timer_start(timer):
    """Reset and start the AXI timer counting up."""
    timer.write(TLR0, 0)
    # Load counter, count up, enable
    timer.write(TCSR0, 0x020)   # LOAD bit
    timer.write(TCSR0, 0x080)   # ENT (enable timer), count up

def timer_read(timer):
    """Read current timer value (cycle count)."""
    return timer.read(TCR0)

def timer_stop(timer):
    """Stop the timer and return the cycle count."""
    cycles = timer.read(TCR0)
    timer.write(TCSR0, 0x000)   # disable
    return cycles

print("\n--- AXI Timer measurement ---")

# Re-run streaming FIR with HW timer
np.copyto(in_buf, x)
out_buf[:] = 0

fir_stream.write(0x10, N_SAMPLES)
fir_stream.write(0x00, 0x01)

timer_start(hw_timer)
dma.sendchannel.transfer(in_buf)
dma.recvchannel.transfer(out_buf)
dma.sendchannel.wait()
dma.recvchannel.wait()
cycles = timer_stop(hw_timer)

FCLK_MHZ = 100.0   # must match your clock
hw_time_us = cycles / FCLK_MHZ
print(f"HW timer: {cycles} cycles = {hw_time_us:.1f} us "
      f"@ {FCLK_MHZ:.0f} MHz")

# ----------------------------------------------------------------
# 6. Comparison summary
# ----------------------------------------------------------------
print("\n--- Summary ---")
print(f"{'Method':<12} {'Time (ms)':>10} {'Speedup':>10}")
print(f"{'MMIO':<12} {t_mmio*1e3:>10.2f} {'1.0x':>10}")
print(f"{'DMA':<12} {t_dma*1e3:>10.2f} {t_mmio/t_dma:>9.1f}x")
print(f"{'HW cycles':<12} {hw_time_us/1e3:>10.3f} {'(PL only)':>10}")

# ----------------------------------------------------------------
# 7. Verify correctness (DMA output vs MMIO output)
# ----------------------------------------------------------------
# Note: both should match since the filter coefficients are identical.
# Small float differences are expected.
max_diff = np.max(np.abs(y_dma - y_mmio))
print(f"\nMax |DMA - MMIO| = {max_diff:.2e}")
if max_diff < 1e-4:
    print("PASS: outputs match")
else:
    print("WARNING: outputs differ -- check shift register reset")

# ----------------------------------------------------------------
# 8. Cleanup
# ----------------------------------------------------------------
in_buf.freebuffer()
out_buf.freebuffer()
