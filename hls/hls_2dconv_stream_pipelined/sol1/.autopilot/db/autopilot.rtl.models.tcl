set SynModuleInfo {
  {SRCNAME conv2d_stream_Pipeline_linebuf_left_to_right MODELNAME conv2d_stream_Pipeline_linebuf_left_to_right RTLNAME conv2d_stream_conv2d_stream_Pipeline_linebuf_left_to_right
    SUBMODULES {
      {MODELNAME conv2d_stream_mul_32s_32s_32_2_1 RTLNAME conv2d_stream_mul_32s_32s_32_2_1 BINDTYPE op TYPE mul IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME conv2d_stream_flow_control_loop_pipe_sequential_init RTLNAME conv2d_stream_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME conv2d_stream_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME conv2d_stream_Pipeline_shift_up MODELNAME conv2d_stream_Pipeline_shift_up RTLNAME conv2d_stream_conv2d_stream_Pipeline_shift_up}
  {SRCNAME conv2d_stream MODELNAME conv2d_stream RTLNAME conv2d_stream IS_TOP 1
    SUBMODULES {
      {MODELNAME conv2d_stream_linebuf_V_0 RTLNAME conv2d_stream_linebuf_V_0 BINDTYPE storage TYPE ram_1wnr IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME conv2d_stream_linebuf_V_2 RTLNAME conv2d_stream_linebuf_V_2 BINDTYPE storage TYPE ram_1wnr IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME conv2d_stream_CTRL_s_axi RTLNAME conv2d_stream_CTRL_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME conv2d_stream_regslice_both RTLNAME conv2d_stream_regslice_both BINDTYPE interface TYPE interface_regslice INSTNAME conv2d_stream_regslice_both_U}
    }
  }
}
