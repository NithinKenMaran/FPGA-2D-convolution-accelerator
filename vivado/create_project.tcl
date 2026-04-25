# create_project.tcl -- Vivado project with block design for 2D convolution
#
# Creates a block design containing:
#   - Zynq PS (Pynq-Z2 preset)
#   - AXI DMA for streaming input/output
#   - Streaming 2D convolution HLS IP (conv2d_stream)
#   - AXI Timer for optional cycle-accurate timing
#
# Usage:
#   vivado -mode batch -source create_project.tcl
#
# Prerequisite:
#   Run HLS first:
#     cd ../hls
#     make pipelined
#   or:
#     make unrolled

# ---------- Configuration ----------
set PROJ_NAME   "lab5_2dconv"
set DESIGN_NAME "conv2d_design"
set PROJ_DIR    "../build"
set PART        "xc7z020clg400-1"
set BOARD       "tul.com.tw:pynq-z2:part0:1.0"

# Choose which HLS directive-set IP Vivado should use.
# Options from your HLS flow:
#   basic
#   pipelined
#   unrolled
set HLS_VARIANT "pipelined"

# Path to HLS-exported IP, relative to vivado/ directory
set CONV2D_IP "../hls/hls_2dconv_stream_${HLS_VARIANT}/sol1/impl/ip"

# ---------- Sanity checks ----------
if {![file exists ${CONV2D_IP}/component.xml]} {
    puts "ERROR: Could not find HLS IP at:"
    puts "  ${CONV2D_IP}"
    puts "Expected:"
    puts "  ${CONV2D_IP}/component.xml"
    puts "Run this first from hls/:"
    puts "  make ${HLS_VARIANT}"
    exit 1
}

# ---------- Create project ----------
create_project ${PROJ_NAME} ${PROJ_DIR}/${PROJ_NAME} -part ${PART} -force
set_property board_part ${BOARD} [current_project]

# Add HLS IP repository
set_property ip_repo_paths [list ${CONV2D_IP}] [current_project]
update_ip_catalog

# ---------- Create block design ----------
create_bd_design ${DESIGN_NAME}

# ---------- Zynq PS ----------
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 ps7

apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 \
    -config {make_external "FIXED_IO, DDR" \
             Master "Disable" Slave "Disable"} [get_bd_cells ps7]

# Enable HP0 port for DMA and set FCLK0 to 100 MHz
set_property -dict [list \
    CONFIG.PCW_USE_S_AXI_HP0 {1} \
    CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {100} \
] [get_bd_cells ps7]

# ---------- AXI DMA ----------
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0

set_property -dict [list \
    CONFIG.c_include_sg {0} \
    CONFIG.c_sg_include_stscntrl_strm {0} \
    CONFIG.c_mm2s_burst_size {256} \
    CONFIG.c_s2mm_burst_size {256} \
    CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]

# ---------- Streaming 2D convolution HLS IP ----------
create_bd_cell -type ip -vlnv ee5332:hls:conv2d_stream:1.0 conv2d_stream_0

# ---------- AXI Timer ----------
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 axi_timer_0

# ---------- Stream connections ----------

# DMA MM2S sends image stream to conv2d
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/M_AXIS_MM2S] \
                    [get_bd_intf_pins conv2d_stream_0/in_stream]

# conv2d sends output stream to DMA S2MM
connect_bd_intf_net [get_bd_intf_pins conv2d_stream_0/out_stream] \
                    [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM]

# ---------- AXI-Lite and memory-mapped connections ----------

# DMA AXI-Lite control
apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
    -config {Clk_master "Auto" Clk_slave "Auto" Clk_xbar "Auto" \
             Master "/ps7/M_AXI_GP0" Slave "/axi_dma_0/S_AXI_LITE" \
             intc_ip "New AXI Interconnect" master_apm "0"} \
    [get_bd_intf_pins axi_dma_0/S_AXI_LITE]

# conv2d AXI-Lite control/registers
apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
    -config {Master "/ps7/M_AXI_GP0" Slave "/conv2d_stream_0/s_axi_CTRL" \
             intc_ip "/ps7_axi_periph" master_apm "0"} \
    [get_bd_intf_pins conv2d_stream_0/s_axi_CTRL]

# AXI Timer AXI-Lite control
apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
    -config {Master "/ps7/M_AXI_GP0" Slave "/axi_timer_0/S_AXI" \
             intc_ip "/ps7_axi_periph" master_apm "0"} \
    [get_bd_intf_pins axi_timer_0/S_AXI]

# DMA memory-mapped read/write ports to PS HP0
apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
    -config {Master "/axi_dma_0/M_AXI_MM2S" Slave "/ps7/S_AXI_HP0" \
             intc_ip "New AXI Interconnect" master_apm "0"} \
    [get_bd_intf_pins ps7/S_AXI_HP0]

apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
    -config {Master "/axi_dma_0/M_AXI_S2MM" Slave "/ps7/S_AXI_HP0" \
             intc_ip "/axi_mem_intercon" master_apm "0"} \
    [get_bd_intf_pins axi_dma_0/M_AXI_S2MM]

# ---------- Validate and save ----------
regenerate_bd_layout
validate_bd_design
save_bd_design

# ---------- Generate wrapper and bitstream ----------
make_wrapper -files [get_files ${DESIGN_NAME}.bd] -top

add_files -norecurse \
    ${PROJ_DIR}/${PROJ_NAME}/${PROJ_NAME}.gen/sources_1/bd/${DESIGN_NAME}/hdl/${DESIGN_NAME}_wrapper.v

launch_runs synth_1 -jobs 4
wait_on_run synth_1

launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

# ---------- Export for Pynq ----------
file mkdir ../pynq

set BIT_FILE [get_property DIRECTORY [get_runs impl_1]]/${DESIGN_NAME}_wrapper.bit
set HWH_DIR  ${PROJ_DIR}/${PROJ_NAME}/${PROJ_NAME}.gen/sources_1/bd/${DESIGN_NAME}/hw_handoff

file copy -force ${BIT_FILE} ../pynq/${DESIGN_NAME}.bit
file copy -force ${HWH_DIR}/${DESIGN_NAME}.hwh ../pynq/${DESIGN_NAME}.hwh

puts "Done."
puts "Copied:"
puts "  ../pynq/${DESIGN_NAME}.bit"
puts "  ../pynq/${DESIGN_NAME}.hwh"