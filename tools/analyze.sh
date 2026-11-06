#!/usr/bin/env bash
# Uso: tools/analyze.sh <dir_extraido>
set -euo pipefail
src="${1:?uso: $0 <dir_extraido>}"
out="docs/analysis"
mkdir -p "$out"
find "$src" -type f \( -name 'rastertoz35*' -o -name 'z35' -o -name 'liblexprintjob*' -o -name 'z35*' \) | while read -r f; do
  n="$(basename "$f")"
  { file "$f"; echo; readelf -h "$f" 2>/dev/null | head -20; } > "$out/$n.info.txt" || true
  strings -a -n 4 "$f" > "$out/$n.strings.txt" || true
  readelf -Ws "$f" > "$out/$n.symbols.txt" 2>/dev/null || true
  objdump -d -M intel "$f" > "$out/$n.disasm.txt" 2>/dev/null || true
  echo "analizado: $n"
done
