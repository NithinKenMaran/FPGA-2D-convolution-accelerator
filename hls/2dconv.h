#ifndef CONV2D_H
#define CONV2D_H

#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>

#define DATA_MODE_INT   0
#define DATA_MODE_FIXED 1
#define DATA_MODE_FLOAT 2

#define DATA_MODE DATA_MODE_FLOAT

#if DATA_MODE == DATA_MODE_INT
    typedef ap_int<32> data_t;
#elif DATA_MODE == DATA_MODE_FIXED
    #include <ap_fixed.h>
    typedef ap_fixed<32, 16> data_t;
#elif DATA_MODE == DATA_MODE_FLOAT
    typedef float data_t;
#endif

typedef ap_axiu<32, 0, 0, 0> axis_t;

#define IH 64
#define IW 64
#define KH 3
#define KW 3

#define OH (IH + KH - 1)   // 66
#define OW (IW + KW - 1)   // 66

#define LINEBUF_W (IW + 4) // 68 for full convolution with 2 zero columns on each side

#define INPUT_STREAM_WORDS  ((IH + KH - 1) * IW) // 66 * 64 = 4224
#define OUTPUT_STREAM_WORDS (OH * OW)            // 66 * 66 = 4356

void conv2d_stream(
    hls::stream<axis_t>& in_stream,
    hls::stream<axis_t>& out_stream,
    data_t k00, data_t k01, data_t k02,
    data_t k10, data_t k11, data_t k12,
    data_t k20, data_t k21, data_t k22
);

#endif