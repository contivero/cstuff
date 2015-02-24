#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "../util.h"

/*
 * stack.h implementation using a linked list.
 */

typedef struct Node Node;
struct Node{
    dataT data;
    Node *next;
};

struct Stack{
    Node* top;
};

Stack*
newstack(){
    Stack* sp = xmalloc(sizeof(*sp));
    sp->top = NULL;
    return sp;
}

void
freestack(Stack* s){
    Node* next;
    Node* np = s->top;

    while(np != NULL){
        next = np->next;
        free(np);
        np = next;
    }
    free(s);
}

void
stackpush(Stack* s, dataT data){
    Node* np = xmalloc(sizeof(*np));
    np->data = data;
    np->next = s->top;
    s->top   = np;
}

dataT
stackpop(Stack* s){
    Node* np;
    dataT data;

    if(stackisempty(s))
        die("Cannot pop an empty stack");

    np = s->top;
    data = np->data;
    s->top = s->top->next;
    free(np);
    return data;
}

dataT
stackpeek(Stack* s){
    if(stackisempty(s))
        die("Cannot pop an empty stack");
    return s->top->data;
}

bool
stackisempty(Stack* s){
    s->top == NULL;
}
