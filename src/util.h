#ifndef _UTIL_H
#define _UTIL_H

/* Retonar o numero de CPUS */
int n_cpus();

/* Retorna a diferenca de clocks */
float diff_time_ms(clock_t t2, clock_t t1);

#endif
