#ifndef _UTIL_H
#define _UTIL_H

extern int *occupied_cores;


/* Retonar o numero de CPUS */
int n_cores();

/* Retorna a diferenca de clocks */
float diff_time_s(clock_t t2, clock_t t1);

#endif
