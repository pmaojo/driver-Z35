/* rastertoz35 — filtro CUPS raster -> Lexmark Z35.
 * Uso CUPS: rastertoz35 job user title copies options [file]
 * Compilar en macOS: make   (requiere las cabeceras de CUPS del SDK) */
#include <cups/raster.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "z35_encode.h"

int main(int argc, char *argv[])
{
    int fd = 0;
    if (argc < 6 || argc > 7) { fprintf(stderr, "ERROR: argumentos invalidos\n"); return 1; }
    if (argc == 7 && (fd = open(argv[6], O_RDONLY)) < 0) { perror("ERROR: open"); return 1; }

    cups_raster_t *ras = cupsRasterOpen(fd, CUPS_RASTER_READ);
    cups_page_header2_t h;
    unsigned char *line = NULL;
    int page = 0;

    if (z35_job_start(stdout) < 0) {
        fprintf(stderr, "ERROR: protocolo Z35 no implementado (ver docs/REVERSE.md)\n");
        return 1;
    }
    while (cupsRasterReadHeader2(ras, &h)) {
        page++;
        fprintf(stderr, "PAGE: %d 1\n", page);
        line = realloc(line, h.cupsBytesPerLine);
        z35_page_start(stdout, h.cupsWidth, h.cupsHeight, h.cupsBytesPerLine,
                       h.cupsNumColors > 1);
        for (unsigned y = 0; y < h.cupsHeight; y++) {
            if (cupsRasterReadPixels(ras, line, h.cupsBytesPerLine) < 1) break;
            z35_write_line(stdout, line, h.cupsBytesPerLine);
        }
        z35_page_end(stdout);
    }
    z35_job_end(stdout);
    free(line);
    cupsRasterClose(ras);
    return 0;
}
