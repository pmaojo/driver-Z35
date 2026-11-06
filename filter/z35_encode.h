#ifndef Z35_ENCODE_H
#define Z35_ENCODE_H
#include <stddef.h>
#include <stdio.h>

/* Interfaz del codificador. Implementación pendiente de docs/PROTOCOL.md. */
int z35_job_start(FILE *out);
int z35_page_start(FILE *out, unsigned width, unsigned height, unsigned bpl, int color);
int z35_write_line(FILE *out, const unsigned char *line, size_t len);
int z35_page_end(FILE *out);
int z35_job_end(FILE *out);
#endif
