#include <hls_stream.h>
#include <ap_int.h>

typedef float data_t;

void conv2d_stream(
    hls::stream<data_t>& in_stream,
    hls::stream<data_t>& out_stream,
    const data_t kernel[3][3]
) {
    data_t linebuf[3][9];
    #pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1

    init_rows:
    for (int r = 0; r < 3; r++){
        init_cols:
        for (int c = 0; c < 9; c++) {
        #pragma HLS PIPELINE II=1
            linebuf[r][c] = 0;
        }
    }

    // note: the image has 5 rows.
    // after feeding 5 rows, make sure to feed 2 more rows of zeros.
    // this ensures that the last window processed
    // is the bottom right one where only 1 pixel overlaps with the kernel.
    each_image_row:
    for (int img_r = 0; img_r < 7; img_r++) {
        linebuf_left_to_right:
        for (int ptr = 0; ptr < 7; ptr++) {
            data_t acc = 0;
            if (ptr < 5) {
                data_t pix = in_stream.read();
                linebuf[2][ptr+2] = pix;
            }
            mac_row:
            for (int kr = 0; kr < 3; kr++) {
            #pragma HLS UNROLL
                mac_col:
                for (int kc = 0; kc < 3; kc++) {
                #pragma HLS UNROLL
                    acc += kernel[kr][kc] * linebuf[kr][ptr+kc];
                }
            }
            out_stream.write(acc);
        }

        shift_up:
        for (int c = 0; c < 9; c++) {
        #pragma HLS PIPELINE II=1
            linebuf[0][c] = linebuf[1][c];
            linebuf[1][c] = linebuf[2][c];
            linebuf[2][c] = 0;
        }
    }
}