#include "2dconv.h"

static data_t axis_to_data(axis_t pkt) {
    data_t x;
    x.range(31, 0) = pkt.data.range(31, 0);
    return x;
}

static axis_t data_to_axis(data_t x, bool last) {
    axis_t pkt;
    pkt.data.range(31, 0) = x.range(31, 0);
    pkt.keep = -1;
    pkt.strb = -1;
    pkt.user = 0;
    pkt.id   = 0;
    pkt.dest = 0;
    pkt.last = last;
    return pkt;
}

void conv2d_stream(
    hls::stream<axis_t>& in_stream,
    hls::stream<axis_t>& out_stream,
    data_t k00, data_t k01, data_t k02,
    data_t k10, data_t k11, data_t k12,
    data_t k20, data_t k21, data_t k22
) {
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream

#pragma HLS INTERFACE s_axilite port=k00 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k01 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k02 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k10 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k11 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k12 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k20 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k21 bundle=CTRL
#pragma HLS INTERFACE s_axilite port=k22 bundle=CTRL

#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

    data_t linebuf[KH][LINEBUF_W];
    data_t kernel[KH][KW];

    kernel[0][0] = k00;
    kernel[0][1] = k01;
    kernel[0][2] = k02;
    kernel[1][0] = k10;
    kernel[1][1] = k11;
    kernel[1][2] = k12;
    kernel[2][0] = k20;
    kernel[2][1] = k21;
    kernel[2][2] = k22;

init_rows:
    for (int r = 0; r < KH; r++) {
    init_cols:
        for (int c = 0; c < LINEBUF_W; c++) {
            linebuf[r][c] = 0;
        }
    }

    int out_count = 0;

each_image_row:
    for (int img_r = 0; img_r < OH; img_r++) {
    linebuf_left_to_right:
        for (int ptr = 0; ptr < OW; ptr++) {

            data_t acc = 0;

            if (ptr < IW) {
                axis_t in_pkt = in_stream.read();
                data_t pix = axis_to_data(in_pkt);
                linebuf[2][ptr + 2] = pix;
            }

        mac_row:
            for (int kr = 0; kr < KH; kr++) {
            mac_col:
                for (int kc = 0; kc < KW; kc++) {
                    acc += kernel[kr][kc] * linebuf[kr][ptr + kc];
                }
            }

            axis_t out_pkt = data_to_axis(acc, out_count == OUTPUT_STREAM_WORDS - 1);
            out_stream.write(out_pkt);

            out_count++;
        }

    shift_up:
        for (int c = 0; c < LINEBUF_W; c++) {
            linebuf[0][c] = linebuf[1][c];
            linebuf[1][c] = linebuf[2][c];
            linebuf[2][c] = 0;
        }
    }
}