#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "../util.h"

typedef struct Node Node;
struct Node {
	elemT elem;
	Node  *next;
};

static Node *
newnode(elemT elem) {
	Node *np = xmalloc(sizeof(*np));

	np->elem = elem;
	np->next = NULL;
	return np;
}

struct Queue {
	Node   *head;
	Node   *tail;
	size_t size;
};

Queue*
newqueue(void) {
	Queue *q = xmalloc(sizeof(*q));
	q->head  = NULL;
	q->size  = 0;
	return q;
}

void
freequeue(Queue *q){
	Node *next;

	for (Node *np = q->head; np; np = next){
		next = np->next;
		free(np);
	}
	free(q);
}

void
enqueue(Queue *q, elemT element){
	Node *np = newnode(element);

	if (!q->head)
		q->head = np;
	else
		q->tail->next = np;

	q->tail = np;
	q->size++;
}

elemT
dequeue(Queue *q){
	if (queueisempty(q))
		die("Cannot dequeue from an empty queue");

	Node *np = q->head;
	q->head  = q->head->next;
	q->size--;

	return np;
}

bool
queueisempty(Queue *q){
	return !q->head;
}

bool
queueisfull(Queue *q){
	return false;
}

size_t
queuesize(Queue *q){
	return q->size;
}
