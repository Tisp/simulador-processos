#include <stdio.h>
#include <stdlib.h>

#include "tracefile.h"


const char *format = "%d %s %d %d";

Tracefile *read_tracefile(char *filename) {

	FILE *fp;
	fp = fopen(filename, "r+");
	Tracefile *tracefile;
	
//	int length = countlines(fp);
	int length = 0;

	int i = 0;
	printf("%d", length);
	fseek(fp, 0, SEEK_SET);

	tracefile = (Tracefile *) malloc(sizeof(Tracefile));
	tracefile->length = length;
	tracefile->trace  = (Trace **) malloc(sizeof(Trace **) * length);

	
	while(fscanf(fp, format, &tracefile->trace[i]->t0, &tracefile->trace[i]->nome, &tracefile->trace[i]->dt, &tracefile->trace[i]->deadline) == 4) {
		printf("%d", tracefile->trace[i]->t0);
		i++;
	}

	fclose(fp);

	return tracefile;
}

int countlines(FILE *stream) {
	
	int lines = 0;
	int t0, dt, deadline;
	char nome[256];

	while(fscanf(stream, format, &t0, &nome, &dt, &deadline) == 4) {
		lines++;
	}
	/* Retorna o ponteiro para o comeco do arquivo */
	return lines;	
}
