#include <hls_stream.h>
#include <ap_int.h>

// ------------------------------------------------------------
// Fixed sizes for your current example
// ------------------------------------------------------------
static constexpr int IMG_H = 5;
static constexpr int IMG_W = 5;
static constexpr int K_H   = 3;
static constexpr int K_W   = 3;

static constexpr int PAD   = K_H - 1;              // 2 zeros on each side
static constexpr int P_H   = IMG_H + 2 * PAD;      // 9
static constexpr int P_W   = IMG_W + 2 * PAD;      // 9

static constexpr int OUT_H = P_H - K_H + 1;        // 7
static constexpr int OUT_W = P_W - K_W + 1;        // 7

typedef float data_t;

// ------------------------------------------------------------
// Top-level HLS function
// - in_stream  : 25 pixels, row-major
// - out_stream : 49 pixels, row-major
// - kernel     : 3x3
//
// Behavior:
//   Internally forms the 9x9 padded image stream,
//   stores only 3 rows at a time in line buffers,
//   emits one output whenever a full 3x3 window is available.
// ------------------------------------------------------------
void conv2d_stream_5x5_3x3(
    hls::stream<data_t>& in_stream,
    hls::stream<data_t>& out_stream,
    const data_t kernel[K_H][K_W]
) {
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream
#pragma HLS INTERFACE s_axilite port=kernel   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return   bundle=CTRL

    // 3 line buffers, each width 9
    data_t linebuf[3][P_W];
#pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1

    // Partition kernel completely so the 9 multiplies can happen in parallel
#pragma HLS ARRAY_PARTITION variable=kernel complete dim=0

    // Initialize line buffers to zero
    init_rows:
    for (int r = 0; r < 3; r++) {
        init_cols:
        for (int c = 0; c < P_W; c++) {
#pragma HLS PIPELINE II=1
            linebuf[r][c] = 0;
        }
    }

    // Scan the internally padded 9x9 image in row-major order
    // pr, pc are coordinates in the padded image
    padded_rows:
    for (int pr = 0; pr < P_H; pr++) {

        // At the start of each new padded row:
        // shift rows up: row1->row0, row2->row1
        shift_up:
        for (int c = 0; c < P_W; c++) {
#pragma HLS PIPELINE II=1
            linebuf[0][c] = linebuf[1][c];
            linebuf[1][c] = linebuf[2][c];
            linebuf[2][c] = 0;
        }

        padded_cols:
        for (int pc = 0; pc < P_W; pc++) {
#pragma HLS PIPELINE II=1

            data_t pix = 0;

            // Generate the padded pixel internally.
            // Real image occupies padded rows 2..6 and cols 2..6.
            if (pr >= PAD && pr < PAD + IMG_H &&
                pc >= PAD && pc < PAD + IMG_W) {
                pix = in_stream.read();
            } else {
                pix = 0;
            }

            // Fill the newest line buffer row
            linebuf[2][pc] = pix;

            // Once we have at least 3 rows and 3 cols,
            // emit one output for the 3x3 window whose
            // bottom-right corner is at (pr, pc).
            //
            // Output coordinates are:
            //   orow = pr - 2
            //   ocol = pc - 2
            if (pr >= K_H - 1 && pc >= K_W - 1) {
                data_t acc = 0;

                // Window top-left is at column (pc - 2)
                // Rows are linebuf[0], linebuf[1], linebuf[2]
                mac_row:
                for (int kr = 0; kr < K_H; kr++) {
#pragma HLS UNROLL
                    mac_col:
                    for (int kc = 0; kc < K_W; kc++) {
#pragma HLS UNROLL
                        acc += linebuf[kr][pc - (K_W - 1) + kc] * kernel[kr][kc];
                    }
                }

                out_stream.write(acc);
            }
        }
    }
}