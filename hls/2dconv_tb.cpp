#include "2dconv.h"
#include <stdio.h>
#include <stdlib.h>


static void reference_conv2d_full_preflipped_kernel(
    data_t image[IH][IW],
    data_t kernel[KH][KW],
    data_t expected[OH][OW]
) {
    data_t padded[OH + 2][OW + 2];

    for (int r = 0; r < OH + 2; r++) {
        for (int c = 0; c < OW + 2; c++) {
            padded[r][c] = 0;
        }
    }

    for (int r = 0; r < IH; r++) {
        for (int c = 0; c < IW; c++) {
            padded[r + 2][c + 2] = image[r][c];
        }
    }

    for (int r = 0; r < OH; r++) {
        for (int c = 0; c < OW; c++) {
            data_t acc = 0;

            for (int kr = 0; kr < KH; kr++) {
                for (int kc = 0; kc < KW; kc++) {
                    acc += padded[r + kr][c + kc] * kernel[kr][kc];
                }
            }

            expected[r][c] = acc;
        }
    }
}

int main() {
    // generating image with values 1, 2, 3, ..., IH*IW
    data_t image[IH][IW];

    for (int r = 0; r < IH; r++) {
        for (int c = 0; c < IW; c++) {
            image[r][c] = r * IW + c + 1;
        }
    }

    data_t kernel[KH][KW] = {
        { -1, -2, -3 },
        { -4, -5, -6 },
        { -7, -8, -9 }
    };

    data_t expected[OH][OW];

    reference_conv2d_full_preflipped_kernel(image, kernel, expected);

    hls::stream<axis_t> in_stream("in_stream");
    hls::stream<axis_t> out_stream("out_stream");


    int input_count = 0;

for (int r = 0; r < OH; r++) {
    for (int c = 0; c < IW; c++) {
        axis_t pkt;

        if (r < IH) {
            pkt.data = (ap_uint<32>)image[r][c];
        } else {
            pkt.data = 0;
        }

        pkt.keep = -1;
        pkt.strb = -1;
        pkt.last = (r == OH - 1 && c == IW - 1);

        in_stream.write(pkt);
        input_count++;
    }
}

    if (input_count != INPUT_STREAM_WORDS) {
        printf("FAIL: testbench wrote %d input words, expected %d\n",
               input_count, INPUT_STREAM_WORDS);
        return 1;
    }

    conv2d_stream(
        in_stream,
        out_stream,
        kernel[0][0], kernel[0][1], kernel[0][2],
        kernel[1][0], kernel[1][1], kernel[1][2],
        kernel[2][0], kernel[2][1], kernel[2][2]
    );

    int errors = 0;

    for (int r = 0; r < OH; r++) {
        for (int c = 0; c < OW; c++) {
            int out_index = r * OW + c;

            if (out_stream.empty()) {
                printf("FAIL: output stream became empty early at output %d\n", out_index);
                return 1;
            }

            axis_t pkt = out_stream.read();
            data_t got = (data_t)pkt.data;
            data_t exp = expected[r][c];

            if (got != exp) {
                printf("MISMATCH at output[%d][%d]: got %d, expected %d\n",
                       r, c, (int)got, (int)exp);
                errors++;
            }

            bool expected_last = (out_index == OUTPUT_STREAM_WORDS - 1);
            bool got_last = pkt.last;

            if (got_last != expected_last) {
                printf("TLAST MISMATCH at output[%d][%d]: got %d, expected %d\n",
                       r, c, (int)got_last, (int)expected_last);
                errors++;
            }
        }
    }

    if (!out_stream.empty()) {
        printf("FAIL: output stream has extra unread data\n");
        errors++;
    }

    if (errors == 0) {
        printf("PASS: 2D convolution output and TLAST matched\n");
    } else {
        printf("FAIL: %d mismatches\n", errors);
    }

    return errors ? 1 : 0;
}