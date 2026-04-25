.PHONY: synth basic pipelined unrolled clean clean_all

DIR ?= unrolled

synth:
	vitis_hls -f synth_stream.tcl -tclargs $(DIR)

basic:
	$(MAKE) synth DIR=basic

pipelined:
	$(MAKE) synth DIR=pipelined

unrolled:
	$(MAKE) synth DIR=unrolled

clean:
	rm -rf hls_2dconv_stream_$(DIR)
	rm -f vitis_hls.log

clean_all:
	rm -rf hls_2dconv_stream_basic
	rm -rf hls_2dconv_stream_pipelined
	rm -rf hls_2dconv_stream_unrolled
	rm -f vitis_hls.log