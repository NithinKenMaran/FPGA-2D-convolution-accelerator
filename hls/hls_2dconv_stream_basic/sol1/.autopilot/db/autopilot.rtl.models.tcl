set SynModuleInfo {
  {SRCNAME conv2d_stream MODELNAME conv2d_stream RTLNAME conv2d_stream IS_TOP 1
    SUBMODULES {
      {MODELNAME conv2d_stream_mul_32s_32s_48_2_1 RTLNAME conv2d_stream_mul_32s_32s_48_2_1 BINDTYPE op TYPE mul IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME conv2d_stream_linebuf_V RTLNAME conv2d_stream_linebuf_V BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME conv2d_stream_kernel_V RTLNAME conv2d_stream_kernel_V BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME conv2d_stream_CTRL_s_axi RTLNAME conv2d_stream_CTRL_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME conv2d_stream_regslice_both RTLNAME conv2d_stream_regslice_both BINDTYPE interface TYPE interface_regslice INSTNAME conv2d_stream_regslice_both_U}
    }
  }
}
