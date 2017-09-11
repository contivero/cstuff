#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "symtab.h"
#include "../util.h"

#define MULTIPLIER     31
#define BALANCE_FACTOR 2.0
#define RESIZE_FACTOR  2

/* Prime size */
#define INIT_SIZE 1009

typedef struct Node Node;
struct Node{
	char *key;
	void *value;
	Node *next;
};

struct Symtab{
	Node **buckets;
	unsigned int size;
	unsigned long entries;
};

static void          expandtable(Symtab *table);
static char          *clonekey(char *key);
static Node          *findnode(Node *np, char *key);
static void          freebucketchain(Node *np);
static void          freebuckets(Node **buckets, int size);
static unsigned long hash(char *key, int nbuckets);
static bool          mustexpand(Symtab *table);

Symtab *
newsymboltable(void){
	Symtab *sp = xmalloc(sizeof(*sp));

	sp->buckets = xcalloc(INIT_SIZE, sizeof(**sp->buckets));
	sp->size    = INIT_SIZE;
	sp->entries = 0;
	return sp;
}

void
freesymboltable(Symtab *table){
	freebuckets(table->buckets, table->size);
	free(table);
}

int
contains(Symtab *table, char *key){
	return lookup(table, 0, key, NULL) != NULL;
}

void
insert(Symtab *table, char *key, void *value){
	unsigned long h = hash(key, table->size);
	Node *np = findnode(table->buckets[h], key);

	if(np){
		np->value = value;
		return;
	}

	np        = xmalloc(sizeof(*np));
	np->key   = clonekey(key);
	np->value = value;
	np->next  = table->buckets[h];
	table->buckets[h] = np;
	table->entries++;
	if(mustexpand(table))
		expandtable(table);
}

int
delete(Symtab *table, char *key){
	unsigned long h = hash(key, table->size);
	Node *np = table->buckets[h];
	Node *prev = NULL;

	while(np && strcmp(np->key, key)){
		prev = np;
		np = np->next;
	}

	if(!np)
		return 0;

	if(prev != NULL)
		prev->next = np->next;
	else
		table->buckets[h] = NULL;

	free(np->key);
	free(np);
	table->entries--;

	return 1;
}

/* lookup with optional insertion
 * See: The practice of programming, page 56
 */
void *
lookup(Symtab *table, int insert, char *key, void *value){
	unsigned long h = hash(key, table->size);
	Node *np = findnode(table->buckets[h], key);

	if(np)
		return np->value;
	if(insert){
		np        = xmalloc(sizeof(*np));
		np->key   = clonekey(key);
		np->value = value;
		np->next  = table->buckets[h];
		table->buckets[h] = np;
		table->entries++;
		if(mustexpand(table))
			expandtable(table);
	}

	return np;
}

/* Assumes int! Used for testing.
 * To print, the symbol table should receive the printing
 * function of the value type
 */
void
print(Symtab *table){
	Node *np;

	for(size_t i = 0; i < table->size; i++){
		np = table->buckets[i];
		while(np){
			printf("%d\n", *(int *)np->value);
			np = np->next;
		}
	}
}

void
mapsymtab(symtabfn fn, Symtab *table, void *clientData){
	unsigned int size = table->size;

	for(size_t i = 0; i < size; i++)
		for(Node *np = table->buckets[i]; np; np = np->next)
			fn(np->key, np->value, clientData);
}

static char *
clonekey(char *key){
	if(!key)
		die("clonekey: cannot copy null key");

	char *s = xmalloc(sizeof(*s) * (strlen(key) + 1));
	strcpy(s, key);
	return s;
}

static Node*
findnode(Node *np, char *key){
	while(np && strcmp(np->key, key) != 0)
		np = np->next;

	return np;
}

static void
freebucketchain(Node *np){
	Node *next;

	while(np){
		next = np->next;
		free(np->key);
		free(np);
		np = next;
	}
}

static unsigned long
hash(char *key, int nbuckets){
	unsigned long hashcode = 0;

	for( ; *key; key++)
		hashcode = hashcode * MULTIPLIER + *key;

	return hashcode % nbuckets;
}

static void
freebuckets(Node **buckets, int size){
	for(size_t i = 0; i < size; i++)
		freebucketchain(buckets[i]);
	free(buckets);
}

static bool
mustexpand(Symtab *table){
	return (double)table->entries / table->size > BALANCE_FACTOR;
}

static void
expandtable(Symtab *table){
	Node **oldbuckets = table->buckets;
	const unsigned int oldsize = table->size;

	table->size *= RESIZE_FACTOR;
	table->buckets = xcalloc(table->size, sizeof(*table->buckets));
	table->entries = 0L;

	for(size_t i = 0; i < oldsize; i++){
		Node *np = oldbuckets[i];
		while(np){
			insert(table, np->key, np->value);
			np = np->next;
		}
	}
	freebuckets(oldbuckets, oldsize);
}
