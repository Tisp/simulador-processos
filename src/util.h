#ifndef _UTIL_H
#define _UTIL_H

extern int *occupied_cores;

typedef struct timespec Timer;

/* Retonar o numero de CPUS */
int n_cores();

/* Retorna a diferenca de clocks */
float diff_time_s (Timer finish, Timer start);

void get_time (Timer *t);

#endif
