set PART     "xc7z020clg400-1"
set CLOCK_NS "10"
set TOP      "conv2d_stream"

# Choose directive set from command line.
# Examples:
#   vitis_hls -f synth_stream.tcl -tclargs basic
#   vitis_hls -f synth_stream.tcl -tclargs pipelined
#   vitis_hls -f synth_stream.tcl -tclargs unrolled
#
# Vitis HLS 2021.1 may expose argv as:
#   {-f synth_stream.tcl -tclargs basic}
# so we explicitly look for -tclargs.

set DIRECTIVE_SET "unrolled"

set idx [lsearch $argv "-tclargs"]

if {$idx >= 0} {
    set arg_idx [expr {$idx + 1}]
    if {$arg_idx < [llength $argv]} {
        set DIRECTIVE_SET [lindex $argv $arg_idx]
    }
} elseif {[llength $argv] >= 1} {
    set DIRECTIVE_SET [lindex $argv end]
}

set PROJ "hls_2dconv_stream_${DIRECTIVE_SET}"

puts "=========================================="
puts " HLS project      : ${PROJ}"
puts " Top function     : ${TOP}"
puts " Directive set    : ${DIRECTIVE_SET}"
puts "=========================================="

open_project ${PROJ} -reset
set_top ${TOP}

add_files 2dconv.cpp
add_files 2dconv.h
add_files -tb 2dconv_tb.cpp

open_solution "sol1" -flow_target vivado -reset
set_part ${PART}
create_clock -period ${CLOCK_NS} -name default

set directive_file "directives/${DIRECTIVE_SET}.tcl"

if {![file exists $directive_file]} {
    puts "ERROR: Directive file $directive_file does not exist."
    exit 1
}

puts "Applying directive file: $directive_file"
source $directive_file

# Skip csim on Ubuntu 24.04 + Vitis HLS 2021.1 due old linker/glibc mismatch.
# csim_design

csynth_design

export_design -format ip_catalog \
    -description "Streaming 2D convolution accelerator (${DIRECTIVE_SET})" \
    -vendor "ee5332" \
    -library "hls" \
    -version "1.0"

exit