.PHONY: synth basic pipelined unrolled aggressive clean clean_all reports

DIR ?= pipelined

synth:
	vitis_hls -f synth_stream.tcl -tclargs $(DIR)

basic:
	$(MAKE) synth DIR=basic

pipelined:
	$(MAKE) synth DIR=pipelined

unrolled:
	$(MAKE) synth DIR=unrolled

aggressive:
	$(MAKE) synth DIR=aggressive

reports:
	./read_reports.sh

clean:
	rm -rf hls_2dconv_stream_$(DIR)
	rm -f vitis_hls.log

clean_all:
	rm -rf hls_2dconv_stream_basic
	rm -rf hls_2dconv_stream_pipelined
	rm -rf hls_2dconv_stream_unrolled
	rm -rf hls_2dconv_stream_aggressive
	rm -f vitis_hls.log