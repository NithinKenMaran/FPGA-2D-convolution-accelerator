#!/usr/bin/env bash
set -euo pipefail

variants=("basic" "pipelined" "unrolled" "aggressive")

echo
echo "=========================================="
echo " HLS Synthesis Summary"
echo "=========================================="

printf "%-12s | %10s | %12s | %12s | %10s | %10s | %10s\n" \
    "Variant" "Latency" "Time(ns)" "DSP" "BRAM" "FF" "LUT"
printf "%-12s-+-%10s-+-%12s-+-%12s-+-%10s-+-%10s-+-%10s\n" \
    "------------" "----------" "------------" "------------" "----------" "----------" "----------"

for v in "${variants[@]}"; do
    rpt="hls_2dconv_stream_${v}/sol1/syn/report/csynth.rpt"

    if [[ ! -f "$rpt" ]]; then
        printf "%-12s | missing report: %s\n" "$v" "$rpt"
        continue
    fi

    python3 - "$v" "$rpt" <<'PY'
import sys

variant = sys.argv[1]
rpt = sys.argv[2]

def clean(x):
    return x.strip()

top = None

with open(rpt, "r", errors="ignore") as f:
    for line in f:
        if "conv2d_stream" in line and "|+" in line:
            cols = [clean(c) for c in line.split("|")]
            top = cols
            break

if top is None:
    print(f"{variant:<12} | could not find top-level row")
    sys.exit(0)

latency = top[4]
time_ns = top[5]
bram = top[10]
dsp = top[11]
ff = top[12]
lut = top[13]

print(f"{variant:<12} | {latency:>10} | {time_ns:>12} | {dsp:>12} | {bram:>10} | {ff:>10} | {lut:>10}")
PY

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

    python3 - "$rpt" <<'PY'
import sys

rpt = sys.argv[1]

wanted = [
    "init_rows",
    "init_cols",
    "init_rows_init_cols",
    "each_image_row",
    "linebuf_left_to_right",
    "mac_row",
    "mac_col",
    "shift_up",
]

def clean(x):
    return x.strip()

rows = []

with open(rpt, "r", errors="ignore") as f:
    for line in f:
        if "|" not in line:
            continue

        cols = [clean(c) for c in line.split("|")]
        if len(cols) < 14:
            continue

        name = cols[1].strip()

        if not name.startswith("o "):
            continue

        loop_name = name[2:].strip()

        if loop_name not in wanted:
            continue

        latency = cols[4]
        iter_lat = cols[6]
        interval = cols[7]
        trip_count = cols[8]
        pipelined = cols[9]

        rows.append((loop_name, latency, iter_lat, interval, trip_count, pipelined))

print(f"{'Loop':<26} | {'Latency':>10} | {'IterLat':>10} | {'II':>8} | {'Trip':>8} | {'Pipelined':>10}")
print(f"{'-'*26}-+-{'-'*10}-+-{'-'*10}-+-{'-'*8}-+-{'-'*8}-+-{'-'*10}")

for loop_name, latency, iter_lat, interval, trip_count, pipelined in rows:
    if not interval or interval == "-":
        interval = "-"
    print(f"{loop_name:<26} | {latency:>10} | {iter_lat:>10} | {interval:>8} | {trip_count:>8} | {pipelined:>10}")
PY

done

echo
echo "=========================================="
echo " Done"
echo "=========================================="