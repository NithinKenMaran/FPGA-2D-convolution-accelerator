#!/usr/bin/env bash
set -euo pipefail

# Run all three HLS directive sets and print a compact report summary.
#
# Usage:
#   ./run_stream.sh
#
# Assumes your Makefile supports:
#   make basic
#   make pipelined
#   make unrolled

variants=("basic" "pipelined" "unrolled")

echo "=========================================="
echo " Running Vitis HLS synthesis variants"
echo "=========================================="

for v in "${variants[@]}"; do
    echo
    echo "------------------------------------------"
    echo " Synthesizing: ${v}"
    echo "------------------------------------------"
    make "${v}"
done

echo
echo "=========================================="
echo " HLS Synthesis Summary"
echo "=========================================="

printf "%-12s | %12s | %12s | %10s | %10s | %10s | %10s\n" \
    "Variant" "Latency" "Time(ns)" "DSP" "BRAM" "FF" "LUT"
printf "%-12s-+-%12s-+-%12s-+-%10s-+-%10s-+-%10s-+-%10s\n" \
    "------------" "------------" "------------" "----------" "----------" "----------" "----------"

for v in "${variants[@]}"; do
    rpt="hls_2dconv_stream_${v}/sol1/syn/report/csynth.rpt"

    if [[ ! -f "$rpt" ]]; then
        printf "%-12s | %s\n" "$v" "MISSING REPORT: $rpt"
        continue
    fi

    # Extract the top-level conv2d_stream row.
    # Example row:
    # |+ conv2d_stream | - | 0.39 | 246 | 2.460e+03 | ... | BRAM | DSP | FF | LUT | URAM |
    row="$(grep -E '^\|[[:space:]]*\+[[:space:]]*conv2d_stream[[:space:]]*\|' "$rpt" | head -n 1)"

    if [[ -z "$row" ]]; then
        printf "%-12s | %s\n" "$v" "Could not find top-level row"
        continue
    fi

    latency="$(echo "$row" | awk -F'|' '{gsub(/ /,"",$5); print $5}')"
    time_ns="$(echo "$row" | awk -F'|' '{gsub(/ /,"",$6); print $6}')"
    bram="$(echo "$row" | awk -F'|' '{gsub(/^ +| +$/,"",$11); print $11}')"
    dsp="$(echo "$row" | awk -F'|' '{gsub(/^ +| +$/,"",$12); print $12}')"
    ff="$(echo "$row" | awk -F'|' '{gsub(/^ +| +$/,"",$13); print $13}')"
    lut="$(echo "$row" | awk -F'|' '{gsub(/^ +| +$/,"",$14); print $14}')"

    printf "%-12s | %12s | %12s | %10s | %10s | %10s | %10s\n" \
        "$v" "$latency" "$time_ns" "$dsp" "$bram" "$ff" "$lut"
done

echo
echo "=========================================="
echo " Key Loop Details"
echo "=========================================="

for v in "${variants[@]}"; do
    rpt="hls_2dconv_stream_${v}/sol1/syn/report/csynth.rpt"

    echo
    echo "------------------------------------------"
    echo " ${v}"
    echo "------------------------------------------"

    if [[ ! -f "$rpt" ]]; then
        echo "Missing report: $rpt"
        continue
    fi

    printf "%-26s | %10s | %10s | %8s | %10s\n" \
        "Loop" "Latency" "IterLat" "II" "Pipelined"
    printf "%-26s-+-%10s-+-%10s-+-%8s-+-%10s\n" \
        "--------------------------" "----------" "----------" "--------" "----------"

    # Print only the loops that matter for your report.
    for loop in \
        "init_rows" \
        "init_cols" \
        "init_rows_init_cols" \
        "each_image_row" \
        "linebuf_left_to_right" \
        "mac_row" \
        "mac_col" \
        "shift_up"
    do
        line="$(grep -E "^\|[[:space:]]*o[[:space:]]+${loop}[[:space:]]*\|" "$rpt" | head -n 1 || true)"

        if [[ -z "$line" ]]; then
            continue
        fi

        loop_name="$(echo "$line" | awk -F'|' '{gsub(/^ +| +$/,"",$2); gsub(/^o +/,"",$2); print $2}')"
        latency="$(echo "$line" | awk -F'|' '{gsub(/ /,"",$5); print $5}')"
        iter_lat="$(echo "$line" | awk -F'|' '{gsub(/ /,"",$7); print $7}')"
        ii="$(echo "$line" | awk -F'|' '{gsub(/ /,"",$8); print $8}')"
        pipelined="$(echo "$line" | awk -F'|' '{gsub(/ /,"",$10); print $10}')"

        [[ -z "$ii" || "$ii" == "-" ]] && ii="-"

        printf "%-26s | %10s | %10s | %8s | %10s\n" \
            "$loop_name" "$latency" "$iter_lat" "$ii" "$pipelined"
    done
done

echo
echo "=========================================="
echo " Done"
echo "=========================================="