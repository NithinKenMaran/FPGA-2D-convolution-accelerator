# directives/basic.tcl
# Educational baseline:
# - Disable automatic pipelining of small loops.
# - Avoid explicit pipelining.
# - Avoid explicit unrolling.
# - Avoid array partitioning unless absolutely needed.

config_compile -pipeline_loops 0

# Explicitly request no unrolling by setting factor 1.
# If any of these fail because HLS does not accept factor 1 on your version,
# comment them out; config_compile -pipeline_loops 0 is the important line.
set_directive_unroll -factor 1 conv2d_stream/mac_row
set_directive_unroll -factor 1 conv2d_stream/mac_col
set_directive_unroll -factor 1 conv2d_stream/init_rows_init_cols
set_directive_unroll -factor 1 conv2d_stream/linebuf_left_to_right
set_directive_unroll -factor 1 conv2d_stream/shift_up
set_directive_unroll -factor 1 conv2d_stream/each_image_row