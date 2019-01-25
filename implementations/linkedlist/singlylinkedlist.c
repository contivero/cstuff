#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "../util.h"
#include "singlylinkedlist.h"

/* From 'The Practice of Programming'
 *
 * Rather than defining an explicit List type, the usual way lists are used in
 * C is to start with a type for the elements, and add a pointer that links to
 * the next element.
 */

/* local prototypes */
static Node* newnode(dataT data);

/* functions */

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

	if (list->first) {
		for (np = list->first; np; np = next) {
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

	if (list->first == NULL) {
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
insertfirst(List *list, dataT data) {
	Node *np = newnode(data);

	if (list->first == NULL) {
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
bool
delete(List *list, dataT data) {
	if (list == NULL)
		return false;

	Node *prev = list->first;
	if (data == list->first->data) {
		list->first = list->first->next;
		list->size--;
		free(prev);
		return true;
	}

	for (Node *np = list->first->next; np; np = np->next) {
		if (data == np->data) {
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
bool
deletefirst(List *list) {
	if (list->first == NULL)
		return false;

	Node *np    = list->first;
	list->first = list->first->next;
	free(np);

	return true;
}

dataT
get(const List *list, size_t index) {
	Node *np = list->first;
	dataT ret;

	while (index && np) {
		np = np->next;
		index--;
	}

	if (index)
		die("List index out of bounds");

	return np->data;
}

void
printlist(const List *list) {
	if (!list)
		return;

	Node *np = list->first;
	if (np)
		printf("%d", np->data);
	for (np = np->next; np; np = np->next) {
		printf(" %d", np->data);
	}
	printf("\n");
}
