#ifndef CONV2D_H
#define CONV2D_H

#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <ap_int.h>

typedef int data_t;
typedef ap_axiu<32, 0, 0, 0> axis_t;

void conv2d_stream(
    hls::stream<axis_t>& in_stream,
    hls::stream<axis_t>& out_stream,
    data_t k00, data_t k01, data_t k02,
    data_t k10, data_t k11, data_t k12,
    data_t k20, data_t k21, data_t k22
);

#endif