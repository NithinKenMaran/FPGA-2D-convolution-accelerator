# directives/aggressive.tcl
# Aggressive outer-loop pipelining version.
#
# Purpose:
#   Demonstrates what happens when a high-level outer loop is pipelined.
#   This may reduce total latency, but usually causes a large increase in
#   DSP/FF/LUT usage because HLS duplicates hardware to overlap row processing.
#
# Educational point:
#   Lower latency is not always better if the resource cost is too high.

# Disable automatic small-loop pipelining first, so only our explicit
# directives control the optimization.
config_compile -pipeline_loops 0

# Partition kernel so all coefficients are independently accessible.
set_directive_array_partition -type complete -dim 0 conv2d_stream kernel

# Partition line buffer across rows. This helps HLS access the three rows
# of the 3x3 window in parallel.
set_directive_array_partition -type complete -dim 1 conv2d_stream linebuf

# Aggressively pipeline the outer row loop.
# This is intentionally more aggressive than pipelining only the inner
# sliding-window loop.
set_directive_pipeline -II 1 conv2d_stream/each_image_row