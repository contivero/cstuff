#include <stdlib.h>
#include "queue.h"
#include "../util.h"

typedef struct Node Node;
struct Node {
    queueElemT elem;
    Node* next;
};

static Node*
newnode(queueElemT elem) {
    Node* np = xmalloc(sizeof(*np));

    np->elem = elem;
    np->next = NULL;
    return np;
}

struct Queue {
    Node* head;
    Node* tail;
};

Queue*
newqueue(void) {
    Queue *qp = xmalloc(sizeof(*qp));
    qp->head = NULL;
    return qp;
}

void
freequeue(Queue *q){
    Node *np, *next;

    for(np = q->head; np != NULL; np = next){
        next = np->next;
        free(np);
    }
    free(q);
}

void
enqueue(Queue *q, queueElemT element){
    Node *np = newnode(element);

    if(q->head == NULL)
        q->head = np;
    else
        q->tail->next = np;
    q->tail = np;
}

queueElemT
dequeue(Queue* q){
    if(queueisempty(q))
        die("Cannot dequeue from an empty queue");

    Node* np = q->head;
    q->head = q->head->next;
    return np;
}

bool
queueisempty(Queue* q){
    return q->head == NULL;
}

bool
queueisfull(Queue* queue){
    return false;
}

int
queuelength(Queue *q){
    Node *np;
    int length = 0;

    for(np = q->head; np != NULL; np = np->next)
        length++;

    return length;
}
