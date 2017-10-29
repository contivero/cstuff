/******************************************************************************
 * Copyright (C) by Cristian Adrián Ontivero                                  *
 *                                                                            *
 * This implementation avoids leaving an empty slot to distinguish between    *
 * the empty and full states. It also takes advantage of the fact that        *
 * unsigned arithmetic wraps nicely. When working with size_t values, letting *
 * them overflow is identical to applying modulo SIZE_MAX + 1 to them.        *
 * Thus, there is no need to apply modulo when storing the indexes, just when *
 * using them to reference an array value.                                    *
 *
 * All this assumes a power of 2 capacity; this must be so for the code to be
 * correct. Another prerequisite is that the capacity can be at most half the
 * range of the index data types. Assuming SIZE_MAX is 2^64-1, the maximum
 * capacity is 2^63-1.
 *                                                                            *
 * All functions are O(1).                                                    *
 ******************************************************************************/

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
	size_t write;
};

/* Under modular arithmetic with modulo power of 2, this mask works as the
 * modulo operator */
size_t
mask(size_t x) {
    return x & (QUEUE_ARRAY_SIZE - 1);
}

size_t
queuesize(Queue *q) {
    return q->write - q->read;
}

bool
queueisempty(Queue *q) {
    return q->read == q->write;
}

bool
queueisfull(Queue *q) {
    return queuesize(q) == QUEUE_ARRAY_SIZE;
}

void
enqueue(Queue *q, elemT x) {
    if (!queueisfull(q))
		die("push: buffer is full");

    q->buffer[mask(q->write++)] = x;
}

elemT
dequeue(Queue *q) {
    if (!queueisempty(q))
		die("pop: buffer is full");

    return q->buffer[mask(q->read++)];
}
