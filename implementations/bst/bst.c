#include <stdlib.h>
#include <string.h>
#include "../util.h"

/* Change comparison function, key and value types as necessary */
#define KEYCMP(a,b) strcmp((a),(b))
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

static Node *newnode(const char *key, const char *value);
static void freenode(Node *np);
static void freerec(Node *np);

BST *
newbst(void){
	BST *bst = xmalloc(sizeof(*bst));

	bst->root = NULL;
	bst->size = 0;

	return bst;
}

Node *
newnode(const char *key, const char *value){
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
		free(np);
		freerec(left);
		freerec(right);
	}
}

void
freebst(BST *bst){
	freerec(bst->root);
	free(bst);
}

char *
lookup(BST *bst, char *key){
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

int
insert(BST *bst, char *key, char *value){
	int cmp;
	Node *np;

	np = bst->root;
	while(np){
		cmp = strcmp(key, np->key);
		if(cmp < 0){
			if(np->left == NULL){
				np->left = newnode(key, value);
				bst->size++;
				return 1;
			}
			np = np->left;
		} else if(cmp > 0){
			if(np->right == NULL){
				np->right = newnode(key, value);
				bst->size++;
				return 1;
			}
			np = np->right;
		}
		else
			break;
	}

	warn("insert: duplicate entry %s ignored\n", key);
	return 0;
}

/* assumes bst is a valid pointer and not NULL */
void
delete(BST *bst, char *key){
	int cmp;
	Node *prev = NULL;
	Node *np = bst->root;

	/* find node to delete */
	while(np && (cmp = KEYCMP(key, np->key))){
		prev = np;
		if(cmp < 0)
			np = np->left;
		else
			np = np->right;
	}

	if(!np)
		return; /* The key to delete wasn't found */

	if(np->left == NULL && np->right == NULL){
		if(!prev){
			freenode(bst->root);
			bst->root = NULL;
		} else {
			freenode(np);
			if(KEYCMP(key, prev->key) < 0)
				prev->left = NULL;
			else 
				prev->right = NULL;
		}
	} else if(np->left == NULL){
		if(!prev){
			np = np->right;
			freenode(bst->root);
			bst->root = np;
		} else {
			if(KEYCMP(key, prev->key) < 0)
				prev->left = np->right;
			else 
				prev->right = np->right;
			freenode(np);
		}
	} else if(np->right == NULL) {
		if(!prev){
			np = np->left;
			freenode(bst->root);
			bst->root = np;
		} else {
			if(KEYCMP(key, prev->key) < 0)
				prev->left = np->left;
			else 
				prev->right = np->left;
			freenode(np);
		}
	} else {
		if(!prev)
			;
	}
}

void
deletevalue(Node *np, keyT key){

}
