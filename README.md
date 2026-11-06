# driver-Z35 — Lexmark Z35 en macOS (Apple Silicon / M4)

Driver de código abierto para la Lexmark Z23/Z25/Z33/Z35 (inyección, USB, host-based).

## Punto de partida

El driver propietario original (`z35llpddk`, backend CUPS `z35`, filtro `rastertoz35`,
`liblexprintjob`) son binarios ELF i386. macOS arm64 no puede ejecutarlos (Rosetta solo
emula x86_64, y macOS ya no carga 32 bits). Hay que reimplementar el protocolo, usando
esos binarios como referencia.

## Arquitectura objetivo

    app -> CUPS -> PDF/raster -> rastertoz35 (filtro) -> backend usb -> Z35

* `filter/rastertoz35.c`: lee raster CUPS, convierte a comandos de la impresora.
* `ppd/lexmark-z35.ppd`: resoluciones, tamaños de papel, color/negro.
* Backend: probar primero el backend `usb` estándar de CUPS; si el protocolo necesita
  lecturas bidireccionales (estado de tinta, handshake), escribir un backend con libusb.

## Estado

- [x] Estructura y flujo de análisis (`tools/`)
- [ ] Obtener binarios originales en `vendor/` (ver `docs/REVERSE.md`)
- [ ] Documentar el protocolo en `docs/PROTOCOL.md`
- [ ] Implementar el codificador en `filter/z35_encode.c`
- [ ] Probar en hardware real

El codificador es hoy un stub: **el protocolo aún no está documentado** y no se ha
inventado nada.
