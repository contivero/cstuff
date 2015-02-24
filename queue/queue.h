#ifndef _queue_h
#define _queue_h

#include <stdbool.h>

typedef void* queueElemT;
typedef struct Queue Queue;

Queue *newqueue(void);
void freequeue(Queue *queue);

void enqueue(Queue *queue, queueElemT element);
queueElemT dequeue(Queue *queue);
bool queueisempty(Queue *queue);
bool queueisfull(Queue *queue);
int queuelength(Queue *queue);

#endif
