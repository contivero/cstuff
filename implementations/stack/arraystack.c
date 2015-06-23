#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "../util.h"

/*
 * stack.h implementation using dynamically allocated arrays
 */

struct Stack {
	dataT *element;
	int    count;
	int    size;
};

static void expandstack(Stack* stack);

Stack *
newstack(void){
	Stack *sp   = xmalloc(sizeof(*sp));
	sp->element = xmalloc(sizeof((*(sp->element))) * INIT_SIZE);
	sp->count   = 0;
	sp->size	= INIT_SIZE;
	return sp;
}

void
freestack(Stack *s){
	free(s->element);
	free(s);
}

void
stackpush(Stack *s, dataT data){
	if(s->count == s->size){
		expandstack(s);
	}
	s->element[s->count++] = data;
}

dataT
stackpop(Stack *s){
	if(stackisempty(s))
		die("Cannot pop an empty stack");
	return s->element[--s->count];
}

dataT
stackpeek(Stack *s){
	if(stackisempty(s))
		die("Cannot peek an empty stack");
	return s->element[s->count - 1];
}

bool
stackisempty(Stack *s){
	return s->count == 0;
}

static void
expandstack(Stack *s){
	s->element = xrealloc(s, sizeof((*(s->element))) * s->size * 2);
}
