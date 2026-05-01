set moduleName conv2d_stream_Pipeline_shift_up
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
set C_modelName {conv2d_stream_Pipeline_shift_up}
set C_modelType { void 0 }
set C_modelArgList {
	{ linebuf_V_1 int 32 regular {array 68 { 0 1 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 } 1 1 }  }
	{ linebuf_V_0 int 32 regular {array 68 { 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 } 0 1 }  }
	{ linebuf_V_2 int 32 regular {array 68 { 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 } 1 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "linebuf_V_1", "interface" : "memory", "bitwidth" : 32, "direction" : "READWRITE"} , 
 	{ "Name" : "linebuf_V_0", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "linebuf_V_2", "interface" : "memory", "bitwidth" : 32, "direction" : "READWRITE"} ]}
# RTL Port declarations: 
set portNum 22
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ linebuf_V_1_address0 sc_out sc_lv 7 signal 0 } 
	{ linebuf_V_1_ce0 sc_out sc_logic 1 signal 0 } 
	{ linebuf_V_1_we0 sc_out sc_logic 1 signal 0 } 
	{ linebuf_V_1_d0 sc_out sc_lv 32 signal 0 } 
	{ linebuf_V_1_address1 sc_out sc_lv 7 signal 0 } 
	{ linebuf_V_1_ce1 sc_out sc_logic 1 signal 0 } 
	{ linebuf_V_1_q1 sc_in sc_lv 32 signal 0 } 
	{ linebuf_V_0_address0 sc_out sc_lv 7 signal 1 } 
	{ linebuf_V_0_ce0 sc_out sc_logic 1 signal 1 } 
	{ linebuf_V_0_we0 sc_out sc_logic 1 signal 1 } 
	{ linebuf_V_0_d0 sc_out sc_lv 32 signal 1 } 
	{ linebuf_V_2_address0 sc_out sc_lv 7 signal 2 } 
	{ linebuf_V_2_ce0 sc_out sc_logic 1 signal 2 } 
	{ linebuf_V_2_we0 sc_out sc_logic 1 signal 2 } 
	{ linebuf_V_2_d0 sc_out sc_lv 32 signal 2 } 
	{ linebuf_V_2_q0 sc_in sc_lv 32 signal 2 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "linebuf_V_1_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "address0" }} , 
 	{ "name": "linebuf_V_1_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "ce0" }} , 
 	{ "name": "linebuf_V_1_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "we0" }} , 
 	{ "name": "linebuf_V_1_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "d0" }} , 
 	{ "name": "linebuf_V_1_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "address1" }} , 
 	{ "name": "linebuf_V_1_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "ce1" }} , 
 	{ "name": "linebuf_V_1_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_1", "role": "q1" }} , 
 	{ "name": "linebuf_V_0_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "address0" }} , 
 	{ "name": "linebuf_V_0_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "ce0" }} , 
 	{ "name": "linebuf_V_0_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "we0" }} , 
 	{ "name": "linebuf_V_0_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_0", "role": "d0" }} , 
 	{ "name": "linebuf_V_2_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "address0" }} , 
 	{ "name": "linebuf_V_2_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "ce0" }} , 
 	{ "name": "linebuf_V_2_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "we0" }} , 
 	{ "name": "linebuf_V_2_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "d0" }} , 
 	{ "name": "linebuf_V_2_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "linebuf_V_2", "role": "q0" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "conv2d_stream_Pipeline_shift_up",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "70", "EstimateLatencyMax" : "70",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "linebuf_V_1", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "linebuf_V_0", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "linebuf_V_2", "Type" : "Memory", "Direction" : "IO"}],
		"Loop" : [
			{"Name" : "shift_up", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter0", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	conv2d_stream_Pipeline_shift_up {
		linebuf_V_1 {Type IO LastRead 0 FirstWrite 1}
		linebuf_V_0 {Type O LastRead -1 FirstWrite 1}
		linebuf_V_2 {Type IO LastRead 0 FirstWrite 0}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "70", "Max" : "70"}
	, {"Name" : "Interval", "Min" : "70", "Max" : "70"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	linebuf_V_1 { ap_memory {  { linebuf_V_1_address0 mem_address 1 7 }  { linebuf_V_1_ce0 mem_ce 1 1 }  { linebuf_V_1_we0 mem_we 1 1 }  { linebuf_V_1_d0 mem_din 1 32 }  { linebuf_V_1_address1 MemPortADDR2 1 7 }  { linebuf_V_1_ce1 MemPortCE2 1 1 }  { linebuf_V_1_q1 MemPortDOUT2 0 32 } } }
	linebuf_V_0 { ap_memory {  { linebuf_V_0_address0 mem_address 1 7 }  { linebuf_V_0_ce0 mem_ce 1 1 }  { linebuf_V_0_we0 mem_we 1 1 }  { linebuf_V_0_d0 mem_din 1 32 } } }
	linebuf_V_2 { ap_memory {  { linebuf_V_2_address0 mem_address 1 7 }  { linebuf_V_2_ce0 mem_ce 1 1 }  { linebuf_V_2_we0 mem_we 1 1 }  { linebuf_V_2_d0 mem_din 1 32 }  { linebuf_V_2_q0 mem_dout 0 32 } } }
}
