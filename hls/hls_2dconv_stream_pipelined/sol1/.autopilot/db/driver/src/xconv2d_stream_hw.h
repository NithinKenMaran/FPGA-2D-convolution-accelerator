// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// CTRL
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of k00
//        bit 31~0 - k00[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of k01
//        bit 31~0 - k01[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of k02
//        bit 31~0 - k02[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of k10
//        bit 31~0 - k10[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of k11
//        bit 31~0 - k11[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of k12
//        bit 31~0 - k12[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of k20
//        bit 31~0 - k20[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of k21
//        bit 31~0 - k21[31:0] (Read/Write)
// 0x4c : reserved
// 0x50 : Data signal of k22
//        bit 31~0 - k22[31:0] (Read/Write)
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCONV2D_STREAM_CTRL_ADDR_AP_CTRL  0x00
#define XCONV2D_STREAM_CTRL_ADDR_GIE      0x04
#define XCONV2D_STREAM_CTRL_ADDR_IER      0x08
#define XCONV2D_STREAM_CTRL_ADDR_ISR      0x0c
#define XCONV2D_STREAM_CTRL_ADDR_K00_DATA 0x10
#define XCONV2D_STREAM_CTRL_BITS_K00_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K01_DATA 0x18
#define XCONV2D_STREAM_CTRL_BITS_K01_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K02_DATA 0x20
#define XCONV2D_STREAM_CTRL_BITS_K02_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K10_DATA 0x28
#define XCONV2D_STREAM_CTRL_BITS_K10_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K11_DATA 0x30
#define XCONV2D_STREAM_CTRL_BITS_K11_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K12_DATA 0x38
#define XCONV2D_STREAM_CTRL_BITS_K12_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K20_DATA 0x40
#define XCONV2D_STREAM_CTRL_BITS_K20_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K21_DATA 0x48
#define XCONV2D_STREAM_CTRL_BITS_K21_DATA 32
#define XCONV2D_STREAM_CTRL_ADDR_K22_DATA 0x50
#define XCONV2D_STREAM_CTRL_BITS_K22_DATA 32

