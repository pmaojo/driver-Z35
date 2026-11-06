# Flujo de ingeniería inversa

1. Poner el paquete original (rpm/deb/tar) en `vendor/` (no se versiona; ver `.gitignore`).
2. `tools/extract.sh vendor/<paquete>` -> extrae a `vendor/extracted/`.
3. `tools/analyze.sh vendor/extracted` -> `file`, `strings`, símbolos y desensamblado
   de `rastertoz35`, `z35` (backend) y `liblexprintjob*` en `docs/analysis/`.
4. Anotar en `docs/PROTOCOL.md`: cabecera de trabajo, comandos por página, formato de
   línea/banda, secuencia de cabezales (negro/color), compresión, fin de página, y
   consultas de estado por el backend.
5. Contrastar con captura USB real (Wireshark/usbmon en Linux, con la impresora
   conectada) cuando se pueda, para validar lo deducido del binario.

Se recomienda Ghidra para el filtro (el análisis estático de `objdump -d` basta para
localizar los `write`/`fwrite` de comandos y tablas).
