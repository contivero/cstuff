#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"
#include "../util.h"

/*
 * stack.h implementation using dynamically allocated arrays
 * size and isempty are O(1). Pop and push too, with the exception of when the
 * array used for the stack needs to be resized.
 */

struct Stack {
	dataT  *element;
	size_t count;    /* elements currently in the stack */
	size_t size;     /* maximum stack size */
};

static void stackresize(Stack* stack, size_t sz);

Stack *
newstack(void) {
	Stack *sp   = xmalloc(sizeof(*sp));
	sp->element = xmalloc(sizeof((*(sp->element))) * INIT_SIZE);
	sp->count   = 0;
	sp->size	= INIT_SIZE;
	return sp;
}

void
freestack(Stack *s) {
	free(s->element);
	free(s);
}

void
stackpush(Stack *s, dataT data) {
	if (s->count == s->size)
		stackresize(s, s->size * 2);

	s->element[s->count++] = data;
}

dataT
stackpop(Stack *s) {
	if (stackisempty(s))
		die("Cannot pop an empty stack");

    dataT data = s->element[--s->count];
    if (s->count > 0 && s->count == s->size/4)
        stackresize(s, s->size/2);
	return data;
}

dataT
stackpeek(Stack *s) {
	if (stackisempty(s))
		die("Cannot peek an empty stack");
	return s->element[s->count - 1];
}

inline bool
stackisempty(Stack *s) {
	return s->count == 0;
}

static void
stackresize(Stack *s, size_t sz) {
	s->element = xrealloc(s->element, sizeof((*(s->element))) * sz);
}
