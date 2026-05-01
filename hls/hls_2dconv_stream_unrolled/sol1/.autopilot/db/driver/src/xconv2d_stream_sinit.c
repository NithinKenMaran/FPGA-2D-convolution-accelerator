// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xconv2d_stream.h"

extern XConv2d_stream_Config XConv2d_stream_ConfigTable[];

XConv2d_stream_Config *XConv2d_stream_LookupConfig(u16 DeviceId) {
	XConv2d_stream_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCONV2D_STREAM_NUM_INSTANCES; Index++) {
		if (XConv2d_stream_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XConv2d_stream_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XConv2d_stream_Initialize(XConv2d_stream *InstancePtr, u16 DeviceId) {
	XConv2d_stream_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XConv2d_stream_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XConv2d_stream_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

