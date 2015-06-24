#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../util.h"
#include "singlylinkedlist.h"

/* From 'The Practice of Programming'
 *
 * Rather than defining an explicit List type, the usual way lists are used in
 * C is to start with a type for the elements, and add a pointer that links to
 * the next element.
 */

/* node's data type */
typedef int dataT;
typedef struct Node Node;

struct Node{
	dataT data;
	Node *next;
};

struct List{
	Node* first;
	Node* last;
	long size;
};

static Node* newnode(dataT data);

static Node*
newnode(dataT data) {
	Node *np = xmalloc(sizeof(*np));

	np->data = data;
	np->next = NULL;
	return np;
}

List *
newlist(void) {
	List *list  = xmalloc(sizeof(*list));

	list->first = list->last = NULL;
	list->size  = 0;
	return list;
}

void
freelist(List *list) {
	Node *np;
	Node *next;

	if(list->first){
		for(np = list->first; np; np = next){
			next = np->next;
			free(np);
		}
	}
	free(list);
}

/* O(1) */
void
insert(List *list, dataT data) {
	Node *np = newnode(data);

	if(list->first == NULL){
		list->first = list->last = np;
		list->size = 1;
		return;
	}

	list->last->next = np;
	list->last = np;
	list->size++;
}

/* O(1) */
void
insertfirst(List *list, dataT data){
	Node *np = newnode(data);

	if(list->first == NULL){
		list->first = list->last = np;
		list->size = 1;
		return;
	}

	np->next = list->first;
	list->first = np;
	list->size++;
}

/*
 * Depending on the data type, an equality function might be needed.
 * Worst case: O(n)
 */
int
delete(List *list, dataT data){
	Node *np;
	Node *prev;

	if(list == NULL)
		return false;

	prev = list->first;
	if(data == list->first->data){
		list->first = list->first->next;
		list->size--;
		free(prev);
		return true;
	}

	for(np = list->first->next; np; np = np->next){
		if(data == np->data){
			prev->next = np->next;
			list->size--;
			free(np);
			return true;
		}
		prev = np;
	}
	return false;
}

/*
 * Complexity: O(1)
 */
int
deletefirst(List *list){
	Node *np;

	if(list->first == NULL)
		return false;

	np = list->first;
	list->first = list->first->next;
	free(np);
}
