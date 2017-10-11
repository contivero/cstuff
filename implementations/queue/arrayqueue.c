/*****************************************************************************
 * Copyright (C) by Cristian Adrián Ontivero                                 *
 *                                                                           *
 * A simple, textbook example of a fixed size queue implementation using a   *
 * circular array. In other words, a ring buffer using an array with         *
 * wrap-around. Eric S. Roberts' implementation in Programming Abstractions  *
 * in C, §10.2.                                                              *
 *                                                                           *
 * It leaves an empty slot to distinguish between the empty and full states. *
 *                                                                           *
 * All functions are O(1).                                                   *
 ****************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "../util.h"

#define QUEUE_SIZE  4095
#define QUEUE_ARRAY_SIZE  (QUEUE_SIZE + 1)

struct Queue {
	elemT  buffer[QUEUE_SIZE];
	size_t head;
	size_t tail;
};

Queue *
newqueue(void){
	Queue *q = xmalloc(sizeof(*q));
	q->head = q->tail = 0U;
	return q;
}

void
freequeue(Queue *q){
	free(q);
}

void
enqueue(Queue *q, elemT element){
	if (queueisfull(q))
		die("enqueue: queue is full");

	q->buffer[q->tail] = element;
	q->tail = (q->tail + 1) % QUEUE_ARRAY_SIZE; /* wrap-around */
}

elemT
dequeue(Queue *q){
	if (queueisempty(q))
		die("dequeue: queue is empty");

	elemT ret = q->buffer[q->head];
	q->head   = (q->head + 1) % QUEUE_ARRAY_SIZE;

	return ret;
}

bool
queueisempty(Queue *q){
	return q->head == q->tail;
}

bool
queueisfull(Queue *q){
    return (q->tail + 1) % QUEUE_ARRAY_SIZE == q->head;
}

/* Determine the number of items. The size of the queue is added in at the
 * beginning to ensure that the left operand of % is always positive. */
size_t
queuesize(Queue *q){
	return (QUEUE_ARRAY_SIZE + q->tail - q->head) % QUEUE_ARRAY_SIZE;
}
