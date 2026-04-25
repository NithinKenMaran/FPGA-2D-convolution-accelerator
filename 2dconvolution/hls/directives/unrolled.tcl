# directives/unrolled.tcl
# Aggressive MAC optimization:
# - Disable automatic loop pipelining first.
# - Explicitly pipeline selected movement/sliding loops.
# - Explicitly unroll the 3x3 MAC loops.

config_compile -pipeline_loops 0

set_directive_array_partition -type complete -dim 0 conv2d_stream kernel
set_directive_array_partition -type complete -dim 1 conv2d_stream linebuf

set_directive_pipeline -II 1 conv2d_stream/init_rows_init_cols
set_directive_pipeline -II 1 conv2d_stream/linebuf_left_to_right
set_directive_pipeline -II 1 conv2d_stream/shift_up

set_directive_unroll conv2d_stream/mac_row
set_directive_unroll conv2d_stream/mac_col