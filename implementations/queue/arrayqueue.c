#include <stdlib.h>
#include "queue.h"
#include "../util.h"

#define QUEUE_SIZE 100
#define QUEUE_ARRAY_SIZE (QUEUE_SIZE + 1)

struct Queue {
	queueElemT element[QUEUE_ARRAY_SIZE];
	int head;
	int tail;
};

Queue *
newqueue(void){
	Queue *qp = xmalloc(sizeof(*qp));
	qp->head = qp->tail = 0;
	return qp;
}

void
freequeue(Queue *q){
	free(q);
}

void
enqueue(Queue *q, queueElemT element){
	if(queueisfull(q))
		die("enqueue: queue is full");

	q->element[q->tail] = element;
	q->tail = (q->tail + 1) % QUEUE_ARRAY_SIZE;
}

queueElemT
dequeue(Queue *q){
	if(queueisempty(q))
		die("dequeue: queue is empty");

	queueElemT ret = q->element[q->head];
	q->head = (q->head + 1) % QUEUE_ARRAY_SIZE;
	return ret;
}

bool
queueisempty(Queue *q){
	return q->head == q->tail;
}

bool
queueisfull(Queue *q){
	return ((q->tail + 1) % QUEUE_ARRAY_SIZE) == q->head;
}

/* size of the queue added at the beginning to ensure that the left operand of
 * % is always positive
 */
int
queuelength(Queue *q){
	return (QUEUE_ARRAY_SIZE + q->tail - q->head) % QUEUE_ARRAY_SIZE;
}
