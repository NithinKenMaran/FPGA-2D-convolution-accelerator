#include "2dconv.h"

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

    data_t linebuf[3][9];
    data_t kernel[3][3];


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
    for (int r = 0; r < 3; r++) {
        init_cols:
        for (int c = 0; c < 9; c++) {
            linebuf[r][c] = 0;
        }
    }

    int out_count = 0;

    each_image_row:
    for (int img_r = 0; img_r < 7; img_r++) {
    linebuf_left_to_right:
        for (int ptr = 0; ptr < 7; ptr++) {

            data_t acc = 0;

            if (ptr < 5) {
                axis_t in_pkt = in_stream.read();
                data_t pix = (data_t) in_pkt.data;
                linebuf[2][ptr + 2] = pix;
            }

        mac_row:
            for (int kr = 0; kr < 3; kr++) {
            mac_col:
                for (int kc = 0; kc < 3; kc++) {
                    acc += kernel[kr][kc] * linebuf[kr][ptr + kc];
                }
            }

            axis_t out_pkt;
            out_pkt.data = acc;
            out_pkt.keep = -1;
            out_pkt.strb = -1;
            out_pkt.user = 0;
            out_pkt.id   = 0;
            out_pkt.dest = 0;

            // 7 x 7 = 49 outputs, so final output has index 48
            out_pkt.last = (out_count == 48);

            out_stream.write(out_pkt);
            out_count++;
        }

    shift_up:
        for (int c = 0; c < 9; c++) {
            linebuf[0][c] = linebuf[1][c];
            linebuf[1][c] = linebuf[2][c];
            linebuf[2][c] = 0;
        }
    }
}