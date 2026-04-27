# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_CTRL {
k00 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 16
	offset_end 23
}
k01 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 24
	offset_end 31
}
k02 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 32
	offset_end 39
}
k10 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 40
	offset_end 47
}
k11 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 48
	offset_end 55
}
k12 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 56
	offset_end 63
}
k20 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 64
	offset_end 71
}
k21 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 72
	offset_end 79
}
k22 { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 80
	offset_end 87
}
ap_start {
	mailbox_input_ctrl 0
	mailbox_output_ctrl 0
	auto_restart_enabled 1
	auto_restart_counter_num 0
	auto_restart_counter_offset 16
	auto_restart_counter_size 32
}
ap_done { }
ap_ready { }
ap_idle { }
}
dict set axilite_register_dict CTRL $port_CTRL


