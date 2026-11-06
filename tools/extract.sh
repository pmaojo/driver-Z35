#!/usr/bin/env bash
# Uso: tools/extract.sh <paquete.{rpm,deb,tar.gz,tgz}>
set -euo pipefail
pkg="${1:?uso: $0 <paquete>}"
out="vendor/extracted"
mkdir -p "$out"
case "$pkg" in
  *.rpm) rpm2cpio "$pkg" | (cd "$out" && cpio -idmv) ;;
  *.deb) dpkg-deb -x "$pkg" "$out" ;;
  *.tar.gz|*.tgz) tar -xzf "$pkg" -C "$out" ;;
  *) echo "formato no soportado: $pkg" >&2; exit 1 ;;
esac
echo "Extraído en $out"
