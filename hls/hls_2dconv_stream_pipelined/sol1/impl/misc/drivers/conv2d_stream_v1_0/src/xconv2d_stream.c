// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xconv2d_stream.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XConv2d_stream_CfgInitialize(XConv2d_stream *InstancePtr, XConv2d_stream_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XConv2d_stream_Start(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL) & 0x80;
    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XConv2d_stream_IsDone(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XConv2d_stream_IsIdle(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XConv2d_stream_IsReady(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XConv2d_stream_EnableAutoRestart(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL, 0x80);
}

void XConv2d_stream_DisableAutoRestart(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL, 0);
}

void XConv2d_stream_Set_k00(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K00_DATA, Data);
}

u32 XConv2d_stream_Get_k00(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K00_DATA);
    return Data;
}

void XConv2d_stream_Set_k01(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K01_DATA, Data);
}

u32 XConv2d_stream_Get_k01(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K01_DATA);
    return Data;
}

void XConv2d_stream_Set_k02(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K02_DATA, Data);
}

u32 XConv2d_stream_Get_k02(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K02_DATA);
    return Data;
}

void XConv2d_stream_Set_k10(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K10_DATA, Data);
}

u32 XConv2d_stream_Get_k10(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K10_DATA);
    return Data;
}

void XConv2d_stream_Set_k11(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K11_DATA, Data);
}

u32 XConv2d_stream_Get_k11(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K11_DATA);
    return Data;
}

void XConv2d_stream_Set_k12(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K12_DATA, Data);
}

u32 XConv2d_stream_Get_k12(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K12_DATA);
    return Data;
}

void XConv2d_stream_Set_k20(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K20_DATA, Data);
}

u32 XConv2d_stream_Get_k20(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K20_DATA);
    return Data;
}

void XConv2d_stream_Set_k21(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K21_DATA, Data);
}

u32 XConv2d_stream_Get_k21(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K21_DATA);
    return Data;
}

void XConv2d_stream_Set_k22(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K22_DATA, Data);
}

u32 XConv2d_stream_Get_k22(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_K22_DATA);
    return Data;
}

void XConv2d_stream_InterruptGlobalEnable(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_GIE, 1);
}

void XConv2d_stream_InterruptGlobalDisable(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_GIE, 0);
}

void XConv2d_stream_InterruptEnable(XConv2d_stream *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER);
    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER, Register | Mask);
}

void XConv2d_stream_InterruptDisable(XConv2d_stream *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER);
    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER, Register & (~Mask));
}

void XConv2d_stream_InterruptClear(XConv2d_stream *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_ISR, Mask);
}

u32 XConv2d_stream_InterruptGetEnabled(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER);
}

u32 XConv2d_stream_InterruptGetStatus(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_ISR);
}

