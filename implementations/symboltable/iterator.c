#include <stdlib.h>
#include <string.h>

#include "iterator.h"
#include "../util.h"

typedef struct Node Node;

struct Node{
	char *key;
	Node *next;
};

struct Iterator{
	Node *current;
};

static void insertkey(char *key, void *value, void *clientData);

Iterator *
newiterator(Symtab *table){
	Iterator *iterator = xmalloc(sizeof(*iterator));
	iterator->current  = NULL;
	mapsymtab(insertkey, table, iterator);
	return iterator;
}

int
stepiterator(Iterator *iterator, char **key){
	Node *np = iterator->current;

	if(!np)
		return 0;

	*key = np->key;
	iterator->current = np->next;
	free(np);
	return 1;
}

void
freeiterator(Iterator *iterator){
	Node *np;

	while(np = iterator->current){
		iterator->current = np->next;
		free(np);
	}
	free(iterator);
}

static void
insertkey(char *key, void *value, void *clientData){
	Iterator *it = (Iterator *) clientData;
	Node *prev = NULL;
	Node *next = it->current;

	while(next && strcmp(key, next->key) > 0){
		prev = next;
		next = next->next;
	}
	Node *np = xmalloc(sizeof(*np));
	np->key = key;
	np->next = next;
	if(!prev)
		it->current = np;
	else
		prev->next = np;
}
