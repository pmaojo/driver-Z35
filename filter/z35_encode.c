#include "z35_encode.h"

/* STUBS: devuelven error hasta documentar el protocolo real. No se emite
 * ningún byte inventado a la impresora. */
int z35_job_start(FILE *out)  { (void)out; return -1; }
int z35_page_start(FILE *out, unsigned w, unsigned h, unsigned bpl, int color)
{ (void)out; (void)w; (void)h; (void)bpl; (void)color; return -1; }
int z35_write_line(FILE *out, const unsigned char *l, size_t n)
{ (void)out; (void)l; (void)n; return -1; }
int z35_page_end(FILE *out)   { (void)out; return -1; }
int z35_job_end(FILE *out)    { (void)out; return -1; }
