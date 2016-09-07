#ifndef _OUTPUT_H
#define _OUTPUT_H

void new_output_file(const char *filename);

void write_output(const char *process_name, float tf, float tr);

void write_contexts(int context);

void close_output();

#endif
