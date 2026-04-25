#!/usr/bin/env bash
set -euo pipefail

variants=("basic" "pipelined" "unrolled" "aggressive")

echo
echo "=========================================="
echo " Running Vitis HLS synthesis variants"
echo "=========================================="

for v in "${variants[@]}"; do
    echo
    echo "------------------------------------------"
    echo " Synthesizing variant: ${v}"
    echo "------------------------------------------"
    make "${v}"
done

echo
echo "=========================================="
echo " Reading HLS reports"
echo "=========================================="

./read_reports.sh