#include <stdio.h>
#include <stdlib.h>

#include "tracefile.h"

int main(int argc, char **argv) {

	Tracefile *tracefile = read_tracefile(argv[1]);
	int i ;

	for(i = 0; i < tracefile->length; i++) {
		printf("%d ", tracefile->trace[i]->t0);
		printf("%s ", tracefile->trace[i]->nome);
		printf("%d ", tracefile->trace[i]->dt);
		printf("%d\n", tracefile->trace[i]->deadline);
	}
	
	tracefile_destroy(tracefile);
	return 0;

}
