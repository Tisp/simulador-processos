#include <stdio.h>
#include <stdlib.h>

static FILE *stream;

void new_output_file(const char *filename) {
    
	stream = fopen(filename, "w+");

	if(!stream) {
		printf("Erro ao abrir o arquivo");
		exit(-1);
	}

}

void write_output(const char *process_name, float tf, float tr) {
    fprintf(stream, "%s %lf %lf\n", process_name, tf, tr);
}

void write_contexts(int context) {
    fprintf(stream, "%d", context);
}

void close_output() {
    fclose(stream);
}
