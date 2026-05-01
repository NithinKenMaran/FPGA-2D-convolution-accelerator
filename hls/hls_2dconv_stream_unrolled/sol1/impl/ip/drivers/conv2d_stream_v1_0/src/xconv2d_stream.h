// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XCONV2D_STREAM_H
#define XCONV2D_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xconv2d_stream_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Ctrl_BaseAddress;
} XConv2d_stream_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XConv2d_stream;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XConv2d_stream_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XConv2d_stream_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XConv2d_stream_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XConv2d_stream_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XConv2d_stream_Initialize(XConv2d_stream *InstancePtr, u16 DeviceId);
XConv2d_stream_Config* XConv2d_stream_LookupConfig(u16 DeviceId);
int XConv2d_stream_CfgInitialize(XConv2d_stream *InstancePtr, XConv2d_stream_Config *ConfigPtr);
#else
int XConv2d_stream_Initialize(XConv2d_stream *InstancePtr, const char* InstanceName);
int XConv2d_stream_Release(XConv2d_stream *InstancePtr);
#endif

void XConv2d_stream_Start(XConv2d_stream *InstancePtr);
u32 XConv2d_stream_IsDone(XConv2d_stream *InstancePtr);
u32 XConv2d_stream_IsIdle(XConv2d_stream *InstancePtr);
u32 XConv2d_stream_IsReady(XConv2d_stream *InstancePtr);
void XConv2d_stream_EnableAutoRestart(XConv2d_stream *InstancePtr);
void XConv2d_stream_DisableAutoRestart(XConv2d_stream *InstancePtr);

void XConv2d_stream_Set_k00(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k00(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k01(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k01(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k02(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k02(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k10(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k10(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k11(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k11(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k12(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k12(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k20(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k20(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k21(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k21(XConv2d_stream *InstancePtr);
void XConv2d_stream_Set_k22(XConv2d_stream *InstancePtr, u32 Data);
u32 XConv2d_stream_Get_k22(XConv2d_stream *InstancePtr);

void XConv2d_stream_InterruptGlobalEnable(XConv2d_stream *InstancePtr);
void XConv2d_stream_InterruptGlobalDisable(XConv2d_stream *InstancePtr);
void XConv2d_stream_InterruptEnable(XConv2d_stream *InstancePtr, u32 Mask);
void XConv2d_stream_InterruptDisable(XConv2d_stream *InstancePtr, u32 Mask);
void XConv2d_stream_InterruptClear(XConv2d_stream *InstancePtr, u32 Mask);
u32 XConv2d_stream_InterruptGetEnabled(XConv2d_stream *InstancePtr);
u32 XConv2d_stream_InterruptGetStatus(XConv2d_stream *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
