#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util.h"

typedef char * valueT;
typedef char * keyT;
typedef struct Node Node;

struct Node{
	keyT key;
	valueT value;
	Node *left;
	Node *right;
};

typedef struct BST{
	Node *root;
	size_t size;
} BST;

/* prototypes */
BST    *newbst(void);
void   freebst(BST *bst);
valueT lookup(BST *bst, keyT key);
void   insert(BST *bst, keyT key, valueT value);
void   delete(BST *bst, keyT key);

static Node *newnode(const keyT key, const valueT value);
static void freenode(Node *np);
static void freerec(Node *np);
static void deletenode(Node *np, Node *prev, int prevcmp);
static void linkprevious(Node *prev, Node *next, int prevcmp);

inline void
linkprevious(Node *prev, Node *next, int prevcmp){
	if(prevcmp < 0)
		prev->left = next;
	else 
		prev->right = next;
}

BST *
newbst(void){
	BST *bst = xmalloc(sizeof(*bst));

	bst->root = NULL;
	bst->size = 0;

	return bst;
}

Node *
newnode(const keyT key, const valueT value){
	Node *np = xmalloc(sizeof(*np));

	np->left  = NULL;
	np->right = NULL;
	np->key   = xmalloc(strlen(key) + 1);
	np->value = xmalloc(strlen(value) + 1);
	strcpy(np->key, key);
	strcpy(np->value, value);

	return np;
}

void
freenode(Node *np){
	free(np->value);
	free(np->key);
	free(np);
}

void
freerec(Node *np){
	if(np){
		Node *right = np->right;
		Node *left  = np->left;
		freenode(np);
		freerec(left);
		freerec(right);
	}
}

void
freebst(BST *bst){
	freerec(bst->root);
	free(bst);
}

valueT
lookup(BST *bst, keyT key){
	int cmp;
	Node *np = bst->root;

	while(np){
		cmp = strcmp(key, np->key);
		if(cmp < 0)
			np = np->left;
		else if(cmp > 0)
			np = np->right;
		else
			return np->value;
	}

	return NULL;
}

void
insert(BST *bst, keyT key, valueT value){
	int cmp;
	Node *np = bst->root;

	if(!np){
		bst->root = newnode(key, value);
		bst->size++;
		return;
	}

	while(np && (cmp = strcmp(key, np->key))){
		if(cmp < 0){
			if(np->left == NULL){
				np->left = newnode(key, value);
				bst->size++;
				return;
			}
			np = np->left;
		} else {
			if(np->right == NULL){
				np->right = newnode(key, value);
				bst->size++;
				return;
			}
			np = np->right;
		}
	}

	warn("insert: duplicate entry %s ignored\n", key);
	return;
}

void
delete(BST *bst, keyT key){
	int cmp, prevcmp;
	Node *prev = NULL;
	Node *np = bst->root;

	/* find node to delete */
	while(np && (cmp = strcmp(key, np->key))){
		prev = np;
		prevcmp = cmp;
		if(cmp < 0)
			np = np->left;
		else
			np = np->right;
	}

	if(!np)
		return; /* key to delete wasn't found */

	if(np->left == NULL){
		if(prev)
			linkprevious(prev, np->right, prevcmp);
		else
			bst->root = np->right;
		freenode(np);
	} else if (np->right == NULL){
		if(prev)
			linkprevious(prev, np->left, prevcmp);
		else
			bst->root = np->left;
		freenode(np);
	} else {
		Node *succprev = NULL;
		Node *succesor = np->left;
		while(succesor->right){
			succprev = succesor;
			succesor = succesor->right;
		}
		succprev->right = succesor->left;
		free(np->key);
		free(np->value);
		np->key = succesor->key;
		np->value = succesor->value;
		free(succesor);
	}
	bst->size--;
}

/* void */
/* printnodes(Node *np){ */
/* 	if(np){ */
/* 		printnodes(np->left); */
/* 		printf("[%s, %s]\n", np->key, np->value); */
/* 		printnodes(np->right); */
/* 	} */
/* } */

/* void */
/* printbst(BST *bst){ */
/* 	if(bst->root){ */
/* 		printf("ROOT: %s | %s\n", bst->root->key, bst->root->value); */
/* 	} */
/* 	printnodes(bst->root); */
/* } */

/* int */
/* main(void){ */
/* 	BST *bst = newbst(); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "3", "c"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "4", "d"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "7", "g"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "9", "i"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "1", "a"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "5", "e"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "2", "b"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "6", "f"); */
/* 	printf("%d\n", bst->size); */
/* 	insert(bst, "8", "h"); */
/* 	printf("%d\n", bst->size); */
/* 	printbst(bst); */
/* 	delete(bst, "1"); */
/* 	printbst(bst); */
/* 	delete(bst, "2"); */
/* 	printbst(bst); */
/* 	delete(bst, "3"); */
/* 	printbst(bst); */
/* 	delete(bst, "4"); */
/* 	printbst(bst); */
/* 	delete(bst, "5"); */
/* 	printbst(bst); */
/* 	delete(bst, "6"); */
/* 	printbst(bst); */
/* 	delete(bst, "7"); */
/* 	printbst(bst); */
/* 	delete(bst, "8"); */
/* 	printbst(bst); */
/* 	delete(bst, "9"); */
/* 	printbst(bst); */
/* 	freebst(bst); */
/* } */
