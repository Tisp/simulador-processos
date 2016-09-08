#ifndef _MULT_QUEUE_H
#define _MULT_QUEUE_H

#define QUANTUM 0.075

void mult_queue(Tracefile *tracefile);
void *worker_mult_queue(void *args);

#endif
