# directives/pipelined.tcl
# Moderate optimization:
# - Disable automatic loop pipelining first.
# - Then explicitly pipeline only the loops we choose.
# - Do not explicitly unroll the MAC loops.
# - Partition only what is needed for clean loop scheduling.

config_compile -pipeline_loops 0

set_directive_array_partition -type complete -dim 0 conv2d_stream kernel
set_directive_array_partition -type complete -dim 1 conv2d_stream linebuf

set_directive_pipeline -II 1 conv2d_stream/init_rows_init_cols
set_directive_pipeline -II 1 conv2d_stream/linebuf_left_to_right
set_directive_pipeline -II 1 conv2d_stream/shift_up

# Explicitly keep the outer loop non-pipelined by simply not applying
# a pipeline directive to each_image_row.
#
# Explicitly keep MAC loops not manually unrolled:
set_directive_unroll -factor 1 conv2d_stream/mac_row
set_directive_unroll -factor 1 conv2d_stream/mac_col