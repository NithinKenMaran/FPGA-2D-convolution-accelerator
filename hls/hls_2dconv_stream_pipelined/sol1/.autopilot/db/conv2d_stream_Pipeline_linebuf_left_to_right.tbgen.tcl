set moduleName conv2d_stream_Pipeline_linebuf_left_to_right
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {conv2d_stream_Pipeline_linebuf_left_to_right}
set C_modelType { void 0 }
set C_modelArgList {
	{ out_count int 13 regular  }
	{ linebuf_V_0 int 32 regular {array 68 { 1 1 1 3 3 3 3 3 3 3 3 3 3 3 3 3 3 } 1 1 }  }
	{ k00 int 32 regular  }
	{ k01 int 32 regular  }
	{ k02 int 32 regular  }
	{ linebuf_V_1 int 32 regular {array 68 { 1 1 1 3 3 3 3 3 3 3 3 3 3 3 3 3 3 } 1 1 }  }
	{ k10 int 32 regular  }
	{ k11 int 32 regular  }
	{ k12 int 32 regular  }
	{ linebuf_V_2 int 32 regular {array 68 { 0 1 1 1 3 3 3 3 3 3 3 3 3 3 3 3 3 } 1 1 }  }
	{ k20 int 32 regular  }
	{ k21 int 32 regular  }
	{ k22 int 32 regular  }
	{ out_stream_V_data_V int 32 regular {axi_s 1 volatile  { out_stream Data } }  }
	{ out_stream_V_keep_V int 4 regular {axi_s 1 volatile  { out_stream Keep } }  }
	{ out_stream_V_strb_V int 4 regular {axi_s 1 volatile  { out_stream Strb } }  }
	{ out_stream_V_last_V int 1 regular {axi_s 1 volatile  { out_stream Last } }  }
	{ in_stream_V_data_V int 32 regular {axi_s 0 volatile  { in_stream Data } }  }
	{ in_stream_V_keep_V int 4 regular {axi_s 0 volatile  { in_stream Keep } }  }
	{ in_stream_V_strb_V int 4 regular {axi_s 0 volatile  { in_stream Strb } }  }
	{ in_stream_V_last_V int 1 regular {axi_s 0 volatile  { in_stream Last } }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "out_count", "interface" : "wire", "bitwidth" : 13, "direction" : "READONLY"} , 
 	{ "Name" : "linebuf_V_0", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k00", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k01", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k02", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "linebuf_V_1", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k10", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k11", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k12", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "linebuf_V_2", "interface" : "memory", "bitwidth" : 32, "direction" : "READWRITE"} , 
 	{ "Name" : "k20", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k21", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k22", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "out_stream_V_data_V", "interface" : "axis", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "out_stream_V_keep_V", "interface" : "axis", "bitwidth" : 4, "direction" : "WRITEONLY"} , 
 	{ "Name" : "out_stream_V_strb_V", "interface" : "axis", "bitwidth" : 4, "direction" : "WRITEONLY"} , 
 	{ "Name" : "out_stream_V_last_V", "interface" : "axis", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "in_stream_V_data_V", "interface" : "axis", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_stream_V_keep_V", "interface" : "axis", "bitwidth" : 4, "direction" : "READONLY"} , 
 	{ "Name" : "in_stream_V_strb_V", "interface" : "axis", "bitwidth" : 4, "direction" : "READONLY"} , 
 	{ "Name" : "in_stream_V_last_V", "interface" : "axis", "bitwidth" : 1, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 59
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ in_stream_TVALID sc_in sc_logic 1 invld 17 } 
	{ out_stream_TREADY sc_in sc_logic 1 outacc 13 } 
	{ out_count sc_in sc_lv 13 signal 0 } 
	{ linebuf_V_0_address0 sc_out sc_lv 7 signal 1 } 
	{ linebuf_V_0_ce0 sc_out sc_logic 1 signal 1 } 
	{ linebuf_V_0_q0 sc_in sc_lv 32 signal 1 } 
	{ linebuf_V_0_address1 sc_out sc_lv 7 signal 1 } 
	{ linebuf_V_0_ce1 sc_out sc_logic 1 signal 1 } 
	{ linebuf_V_0_q1 sc_in sc_lv 32 signal 1 } 
	{ linebuf_V_0_address2 sc_out sc_lv 7 signal 1 } 
	{ linebuf_V_0_ce2 sc_out sc_logic 1 signal 1 } 
	{ linebuf_V_0_q2 sc_in sc_lv 32 signal 1 } 
	{ k00 sc_in sc_lv 32 signal 2 } 
	{ k01 sc_in sc_lv 32 signal 3 } 
	{ k02 sc_in sc_lv 32 signal 4 } 
	{ linebuf_V_1_address0 sc_out sc_lv 7 signal 5 } 
	{ linebuf_V_1_ce0 sc_out sc_logic 1 signal 5 } 
	{ linebuf_V_1_q0 sc_in sc_lv 32 signal 5 } 
	{ linebuf_V_1_address1 sc_out sc_lv 7 signal 5 } 
	{ linebuf_V_1_ce1 sc_out sc_logic 1 signal 5 } 
	{ linebuf_V_1_q1 sc_in sc_lv 32 signal 5 } 
	{ linebuf_V_1_address2 sc_out sc_lv 7 signal 5 } 
	{ linebuf_V_1_ce2 sc_out sc_logic 1 signal 5 } 
	{ linebuf_V_1_q2 sc_in sc_lv 32 signal 5 } 
	{ k10 sc_in sc_lv 32 signal 6 } 
	{ k11 sc_in sc_lv 32 signal 7 } 
	{ k12 sc_in sc_lv 32 signal 8 } 
	{ linebuf_V_2_address0 sc_out sc_lv 7 signal 9 } 
	{ linebuf_V_2_ce0 sc_out sc_logic 1 signal 9 } 
	{ linebuf_V_2_we0 sc_out sc_logic 1 signal 9 } 
	{ linebuf_V_2_d0 sc_out sc_lv 32 signal 9 } 
	{ linebuf_V_2_address1 sc_out sc_lv 7 signal 9 } 
	{ linebuf_V_2_ce1 sc_out sc_logic 1 signal 9 } 
	{ linebuf_V_2_q1 sc_in sc_lv 32 signal 9 } 
	{ linebuf_V_2_address2 sc_out sc_lv 7 signal 9 } 
	{ linebuf_V_2_ce2 sc_out sc_logic 1 signal 9 } 
	{ linebuf_V_2_q2 sc_in sc_lv 32 signal 9 } 
	{ linebuf_V_2_address3 sc_out sc_lv 7 signal 9 } 
	{ linebuf_V_2_ce3 sc_out sc_logic 1 signal 9 } 
	{ linebuf_V_2_q3 sc_in sc_lv 32 signal 9 } 
	{ k20 sc_in sc_lv 32 signal 10 } 
	{ k21 sc_in sc_lv 32 signal 11 } 
	{ k22 sc_in sc_lv 32 signal 12 } 
	{ out_stream_TDATA sc_out sc_lv 32 signal 13 } 
	{ out_stream_TVALID sc_out sc_logic 1 outvld 16 } 
	{ out_stream_TKEEP sc_out sc_lv 4 signal 14 } 
	{ out_stream_TSTRB sc_out sc_lv 4 signal 15 } 
	{ out_stream_TLAST sc_out sc_lv 1 signal 16 } 
	{ in_stream_TDATA sc_in sc_lv 32 signal 17 } 
	{ in_stream_TREADY sc_out sc_logic 1 inacc 20 } 
	{ in_stream_TKEEP sc_in sc_lv 4 signal 18 } 
	{ in_stream_TSTRB sc_in sc_lv 4 signal 19 } 
	{ in_stream_TLAST sc_in sc_lv 1 signal 20 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "in_stream_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "in_stream_V_data_V", "role": "default" }} , 
 	{ "name": "out_stream_TREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "outacc", "bundle":{"name": "out_stream_V_data_V", "role": "default" }} , 
 	{ "name": "out_count", "direction": "in", "datatype": "sc_lv", "bitwidth":13, "type": "signal", "bundle":{"name": "out_count", "role": "default" }} , 
 	{ "name": "linebuf_V_0_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "address0" }} , 
 	{ "name": "linebuf_V_0_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "ce0" }} , 
 	{ "name": "linebuf_V_0_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "q0" }} , 
 	{ "name": "linebuf_V_0_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "address1" }} , 
 	{ "name": "linebuf_V_0_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "ce1" }} , 
 	{ "name": "linebuf_V_0_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "q1" }} , 
 	{ "name": "linebuf_V_0_address2", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "address2" }} , 
 	{ "name": "linebuf_V_0_ce2", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "ce2" }} , 
 	{ "name": "linebuf_V_0_q2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "q2" }} , 
 	{ "name": "k00", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k00", "role": "default" }} , 
 	{ "name": "k01", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k01", "role": "default" }} , 
 	{ "name": "k02", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k02", "role": "default" }} , 
 	{ "name": "linebuf_V_1_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "address0" }} , 
 	{ "name": "linebuf_V_1_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "ce0" }} , 
 	{ "name": "linebuf_V_1_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "q0" }} , 
 	{ "name": "linebuf_V_1_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "address1" }} , 
 	{ "name": "linebuf_V_1_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "ce1" }} , 
 	{ "name": "linebuf_V_1_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "q1" }} , 
 	{ "name": "linebuf_V_1_address2", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "address2" }} , 
 	{ "name": "linebuf_V_1_ce2", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "ce2" }} , 
 	{ "name": "linebuf_V_1_q2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "q2" }} , 
 	{ "name": "k10", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k10", "role": "default" }} , 
 	{ "name": "k11", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k11", "role": "default" }} , 
 	{ "name": "k12", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k12", "role": "default" }} , 
 	{ "name": "linebuf_V_2_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "address0" }} , 
 	{ "name": "linebuf_V_2_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "ce0" }} , 
 	{ "name": "linebuf_V_2_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "we0" }} , 
 	{ "name": "linebuf_V_2_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "d0" }} , 
 	{ "name": "linebuf_V_2_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "address1" }} , 
 	{ "name": "linebuf_V_2_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "ce1" }} , 
 	{ "name": "linebuf_V_2_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "q1" }} , 
 	{ "name": "linebuf_V_2_address2", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "address2" }} , 
 	{ "name": "linebuf_V_2_ce2", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "ce2" }} , 
 	{ "name": "linebuf_V_2_q2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "q2" }} , 
 	{ "name": "linebuf_V_2_address3", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "address3" }} , 
 	{ "name": "linebuf_V_2_ce3", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "ce3" }} , 
 	{ "name": "linebuf_V_2_q3", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "q3" }} , 
 	{ "name": "k20", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k20", "role": "default" }} , 
 	{ "name": "k21", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k21", "role": "default" }} , 
 	{ "name": "k22", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k22", "role": "default" }} , 
 	{ "name": "out_stream_TDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_stream_V_data_V", "role": "default" }} , 
 	{ "name": "out_stream_TVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "out_stream_V_last_V", "role": "default" }} , 
 	{ "name": "out_stream_TKEEP", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "out_stream_V_keep_V", "role": "default" }} , 
 	{ "name": "out_stream_TSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "out_stream_V_strb_V", "role": "default" }} , 
 	{ "name": "out_stream_TLAST", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "out_stream_V_last_V", "role": "default" }} , 
 	{ "name": "in_stream_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_stream_V_data_V", "role": "default" }} , 
 	{ "name": "in_stream_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "in_stream_V_last_V", "role": "default" }} , 
 	{ "name": "in_stream_TKEEP", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "in_stream_V_keep_V", "role": "default" }} , 
 	{ "name": "in_stream_TSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "in_stream_V_strb_V", "role": "default" }} , 
 	{ "name": "in_stream_TLAST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "in_stream_V_last_V", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"],
		"CDFG" : "conv2d_stream_Pipeline_linebuf_left_to_right",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "74", "EstimateLatencyMax" : "74",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "out_count", "Type" : "None", "Direction" : "I"},
			{"Name" : "linebuf_V_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "k00", "Type" : "None", "Direction" : "I"},
			{"Name" : "k01", "Type" : "None", "Direction" : "I"},
			{"Name" : "k02", "Type" : "None", "Direction" : "I"},
			{"Name" : "linebuf_V_1", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "k10", "Type" : "None", "Direction" : "I"},
			{"Name" : "k11", "Type" : "None", "Direction" : "I"},
			{"Name" : "k12", "Type" : "None", "Direction" : "I"},
			{"Name" : "linebuf_V_2", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "k20", "Type" : "None", "Direction" : "I"},
			{"Name" : "k21", "Type" : "None", "Direction" : "I"},
			{"Name" : "k22", "Type" : "None", "Direction" : "I"},
			{"Name" : "out_stream_V_data_V", "Type" : "Axis", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "out_stream_TDATA_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "out_stream_V_keep_V", "Type" : "Axis", "Direction" : "O"},
			{"Name" : "out_stream_V_strb_V", "Type" : "Axis", "Direction" : "O"},
			{"Name" : "out_stream_V_last_V", "Type" : "Axis", "Direction" : "O"},
			{"Name" : "in_stream_V_data_V", "Type" : "Axis", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "in_stream_TDATA_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "in_stream_V_keep_V", "Type" : "Axis", "Direction" : "I"},
			{"Name" : "in_stream_V_strb_V", "Type" : "Axis", "Direction" : "I"},
			{"Name" : "in_stream_V_last_V", "Type" : "Axis", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "linebuf_left_to_right", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter7", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter7", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U1", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U2", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U3", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U4", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U5", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U6", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U7", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U8", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U9", "Parent" : "0"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	conv2d_stream_Pipeline_linebuf_left_to_right {
		out_count {Type I LastRead 0 FirstWrite -1}
		linebuf_V_0 {Type I LastRead 1 FirstWrite -1}
		k00 {Type I LastRead 0 FirstWrite -1}
		k01 {Type I LastRead 0 FirstWrite -1}
		k02 {Type I LastRead 0 FirstWrite -1}
		linebuf_V_1 {Type I LastRead 1 FirstWrite -1}
		k10 {Type I LastRead 0 FirstWrite -1}
		k11 {Type I LastRead 0 FirstWrite -1}
		k12 {Type I LastRead 0 FirstWrite -1}
		linebuf_V_2 {Type IO LastRead 2 FirstWrite 0}
		k20 {Type I LastRead 0 FirstWrite -1}
		k21 {Type I LastRead 0 FirstWrite -1}
		k22 {Type I LastRead 0 FirstWrite -1}
		out_stream_V_data_V {Type O LastRead -1 FirstWrite 7}
		out_stream_V_keep_V {Type O LastRead -1 FirstWrite 7}
		out_stream_V_strb_V {Type O LastRead -1 FirstWrite 7}
		out_stream_V_last_V {Type O LastRead -1 FirstWrite 7}
		in_stream_V_data_V {Type I LastRead 0 FirstWrite -1}
		in_stream_V_keep_V {Type I LastRead 0 FirstWrite -1}
		in_stream_V_strb_V {Type I LastRead 0 FirstWrite -1}
		in_stream_V_last_V {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "74", "Max" : "74"}
	, {"Name" : "Interval", "Min" : "74", "Max" : "74"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	out_count { ap_none {  { out_count in_data 0 13 } } }
	linebuf_V_0 { ap_memory {  { linebuf_V_0_address0 mem_address 1 7 }  { linebuf_V_0_ce0 mem_ce 1 1 }  { linebuf_V_0_q0 mem_dout 0 32 }  { linebuf_V_0_address1 MemPortADDR2 1 7 }  { linebuf_V_0_ce1 MemPortCE2 1 1 }  { linebuf_V_0_q1 MemPortDOUT2 0 32 }  { linebuf_V_0_address2 MemPortADDR2 1 7 }  { linebuf_V_0_ce2 MemPortCE2 1 1 }  { linebuf_V_0_q2 MemPortDOUT2 0 32 } } }
	k00 { ap_none {  { k00 in_data 0 32 } } }
	k01 { ap_none {  { k01 in_data 0 32 } } }
	k02 { ap_none {  { k02 in_data 0 32 } } }
	linebuf_V_1 { ap_memory {  { linebuf_V_1_address0 mem_address 1 7 }  { linebuf_V_1_ce0 mem_ce 1 1 }  { linebuf_V_1_q0 mem_dout 0 32 }  { linebuf_V_1_address1 MemPortADDR2 1 7 }  { linebuf_V_1_ce1 MemPortCE2 1 1 }  { linebuf_V_1_q1 MemPortDOUT2 0 32 }  { linebuf_V_1_address2 MemPortADDR2 1 7 }  { linebuf_V_1_ce2 MemPortCE2 1 1 }  { linebuf_V_1_q2 MemPortDOUT2 0 32 } } }
	k10 { ap_none {  { k10 in_data 0 32 } } }
	k11 { ap_none {  { k11 in_data 0 32 } } }
	k12 { ap_none {  { k12 in_data 0 32 } } }
	linebuf_V_2 { ap_memory {  { linebuf_V_2_address0 mem_address 1 7 }  { linebuf_V_2_ce0 mem_ce 1 1 }  { linebuf_V_2_we0 mem_we 1 1 }  { linebuf_V_2_d0 mem_din 1 32 }  { linebuf_V_2_address1 MemPortADDR2 1 7 }  { linebuf_V_2_ce1 MemPortCE2 1 1 }  { linebuf_V_2_q1 MemPortDOUT2 0 32 }  { linebuf_V_2_address2 MemPortADDR2 1 7 }  { linebuf_V_2_ce2 MemPortCE2 1 1 }  { linebuf_V_2_q2 MemPortDOUT2 0 32 }  { linebuf_V_2_address3 MemPortADDR2 1 7 }  { linebuf_V_2_ce3 MemPortCE2 1 1 }  { linebuf_V_2_q3 MemPortDOUT2 0 32 } } }
	k20 { ap_none {  { k20 in_data 0 32 } } }
	k21 { ap_none {  { k21 in_data 0 32 } } }
	k22 { ap_none {  { k22 in_data 0 32 } } }
	out_stream_V_data_V { axis {  { out_stream_TREADY out_acc 0 1 }  { out_stream_TDATA out_data 1 32 } } }
	out_stream_V_keep_V { axis {  { out_stream_TKEEP out_data 1 4 } } }
	out_stream_V_strb_V { axis {  { out_stream_TSTRB out_data 1 4 } } }
	out_stream_V_last_V { axis {  { out_stream_TVALID out_vld 1 1 }  { out_stream_TLAST out_data 1 1 } } }
	in_stream_V_data_V { axis {  { in_stream_TVALID in_vld 0 1 }  { in_stream_TDATA in_data 0 32 } } }
	in_stream_V_keep_V { axis {  { in_stream_TKEEP in_data 0 4 } } }
	in_stream_V_strb_V { axis {  { in_stream_TSTRB in_data 0 4 } } }
	in_stream_V_last_V { axis {  { in_stream_TREADY in_acc 1 1 }  { in_stream_TLAST in_data 0 1 } } }
}
