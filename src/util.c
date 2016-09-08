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
float diff_time_s (clock_t t2, clock_t t1) {
    return ((float)(t2 - t1) / CLOCKS_PER_SEC); 
}



