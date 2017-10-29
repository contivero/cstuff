/***************************************************************************
 * Copyright (C) by Cristian Adrián Ontivero                               *
 *                                                                         *
 * This implementation avoids leaving an empty slot to distinguish between *
 * the empty and full states.                                              *
 *                                                                         *
 * All functions are O(1).                                                 *
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"
#include "../util.h"

#define QUEUE_SIZE  4095

/* Note: it MUST be a power of 2! */
#define QUEUE_ARRAY_SIZE  (QUEUE_SIZE + 1)

struct Queue {
	elemT  buffer[QUEUE_ARRAY_SIZE];
	size_t read;
	size_t length; /* amount of elements in the buffer */
};

/* Under modular arithmetic with modulo power of 2, this mask works as the
 * modulo operator */
size_t
mask(size_t x) {
    return x & (QUEUE_ARRAY_SIZE - 1);
}

bool
queueisempty(Queue *q) {
    return q->length == 0;
}

bool
queueisfull(Queue *q) {
    return q->length == QUEUE_ARRAY_SIZE;
}

size_t
queuesize(Queue *q) {
    return q->length;
}

void
enqueue(Queue *q, elemT x) {
    if (!queueisfull(q))
		die("push: buffer is full");

    q->buffer[mask(q->read + q->length++)] = x;
}

elemT
dequeue(Queue *q) {
    if (!queueisempty(q))
		die("pop: buffer is full");

    elemT ret = q->buffer[q->read];
    q->read   = mask(q->read + 1);
    q->length--;
    return ret;
}
