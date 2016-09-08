#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "util.h"

/* Retorna o numero de CPUS */
int n_cores() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

/* Retonar em segundos a diferenca de dois times */
float diff_time_s (Timer finish, Timer start) {
    float elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    return elapsed; 
}

void get_time(Timer *t) {
    clock_gettime(CLOCK_MONOTONIC, t);
}



