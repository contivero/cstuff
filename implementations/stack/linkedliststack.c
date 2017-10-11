#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "../util.h"

/*
 * stack.h implementation using a linked list.
 * push, pop, size, and isempty all O(1)
 */

typedef struct Node Node;
struct Node{
	dataT data;
	Node  *next;
};

struct Stack{
	Node   *top;
    size_t size;
};

Stack *
newstack() {
	Stack *sp = xmalloc(sizeof(*sp));
	sp->top   = NULL;
	sp->size  = 0;
	return sp;
}

void
freestack(Stack *s) {
	Node *next;
	Node *np = s->top;

	while (np) {
		next = np->next;
		free(np);
		np = next;
	}
	free(s);
}

void
stackpush(Stack *s, dataT data) {
	Node *np = xmalloc(sizeof(*np));

	np->data = data;
	np->next = s->top;
	s->top   = np;
    s->size++;
}

dataT
stackpop(Stack *s) {
	if (stackisempty(s))
		die("Cannot pop an empty stack");

	Node *np   = s->top;
	dataT data = np->data;
	s->top     = s->top->next;
    s->size++;
	free(np);

	return data;
}

dataT
stackpeek(Stack *s) {
	if (stackisempty(s))
		die("Cannot pop an empty stack");

	return s->top->data;
}

size_t
stacksize(Stack *s) {
    return s->size;
}

bool
stackisempty(Stack *s) {
	s->top == 0;
}
