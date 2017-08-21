#include <stdlib.h>
#include <string.h>
#include "../util.h"
#include <stdio.h>

/*
 * http://www.superstarcoders.com/blogs/posts/efficient-avl-tree-in-c-sharp.aspx
 */
typedef char * valueT;
typedef char * keyT;
typedef struct Node Node;

struct Node{
	keyT key;
	valueT value;
	int balancefactor;
	Node *left;
	Node *right;
	Node *parent;
};

typedef struct AVL{
	Node *root;
	size_t size;
} AVL;

void rebalanceAVL(AVL *avl, Node *np, int balance);
AVL  *newAVL(void);
Node *newNode(const keyT key, const valueT value, Node *parent);
void freeNode(Node *np);
void freerec(Node *np);

void freeAVL(AVL *avl);

AVL *
newAVL(void){
	AVL *avl = xmalloc(sizeof(*avl));

	avl->root = NULL;
	avl->size = 0;

	return avl;
}

Node *
newNode(const keyT key, const valueT value, Node *parent){
	Node *np = xmalloc(sizeof(*np));

	np->balancefactor = 0;
	np->left   = NULL;
	np->right  = NULL;
	np->parent = parent;
	np->key    = xmalloc(strlen(key) + 1);
	np->value  = xmalloc(strlen(value) + 1);
	strcpy(np->key, key);
	strcpy(np->value, value);

	return np;
}

void
freeNode(Node *np){
	free(np->value);
	free(np->key);
	free(np);
}

void
freerec(Node *np){
	if(np){
		Node *right = np->right;
		Node *left  = np->left;
		freeNode(np);
		freerec(left);
		freerec(right);
	}
}

void
freeAVL(AVL *avl){
	freerec(avl->root);
	free(avl);
}

valueT
lookup(const AVL *avl, keyT key){
	int cmp;
	Node *np = avl->root;

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

Node *
rotateleft(AVL *avl, Node *np){
	Node *right = np->right;
	Node *rightleft = right->left;
	Node *parent = np->parent;

	if(rightleft)
		rightleft->parent = np;

	if(np == avl->root)
		avl->root = right;
	else if(parent->right == np)
		parent->right = right;
	else
		parent->left = right;

	right->balancefactor++;
	np->balancefactor = -right->balancefactor;

	return right;
}

Node *
rotateright(AVL *avl, Node *np){
    Node *left = np->left;
    Node *leftright = left->right;
    Node *parent = np->parent;

    left->parent = parent;
    left->right  = np;
    np->left     = leftright;
    np->parent   = left;

    if (leftright)
        leftright->parent = np;

    if (np == avl->root)
        avl->root = left;
    else if(parent->left == np)
        parent->left = left;
    else
        parent->right = left;

    left->balancefactor--;
    np->balancefactor = -left->balancefactor;

    return left;
}

Node *
rotateleftright(AVL *avl, Node *np){
	Node *left = np->left;
    Node *leftright = left->right;
    Node *parent = np->parent;
    Node *leftrightright = leftright->right;
    Node *leftrightleft = leftright->left;

    leftright->parent = parent;
    np->left = leftrightright;
    left->right = leftrightleft;
    leftright->left = left;
    leftright->right = np;
    left->parent = leftright;
    np->parent = leftright;

    if (leftrightright)
        leftrightright->parent = np;
    if (leftrightleft)
        leftrightleft->parent = left;

    if (np == avl->root)
        avl->root = leftright;
    else if (parent->left == np)
        parent->left = leftright;
    else
        parent->right = leftright;

    if (leftright->balancefactor == -1){
        np->balancefactor = 0;
        left->balancefactor = 1;
    } else if(leftright->balancefactor == 0){
        np->balancefactor = 0;
        left->balancefactor = 0;
    } else {
        np->balancefactor = -1;
        left->balancefactor = 0;
    }

    leftright->balancefactor = 0;

    return leftright;
}

Node *
rotaterightleft(AVL *avl, Node *np){
	Node *right          = np->right;
    Node *rightleft      = right->left;
    Node *parent         = np->parent;
    Node *rightleftleft  = rightleft->left;
    Node *rightleftright = rightleft->right;

    rightleft->parent = parent;
    np->right         = rightleftleft;
    right->left       = rightleftright;
    rightleft->right  = right;
    rightleft->left   = np;
    right->parent     = rightleft;
    np->parent        = rightleft;

    if (rightleftleft)
        rightleftleft->parent = np;
    if (rightleftright)
        rightleftright->parent = right;

    if (np == avl->root)
        avl->root = rightleft;
    else if (parent->right == np)
        parent->right = rightleft;
    else
        parent->left = rightleft;

    if (rightleft->balancefactor == 1) {
        np->balancefactor = 0;
        right->balancefactor = -1;
    } else if (rightleft->balancefactor == 0) {
        np->balancefactor = 0;
        right->balancefactor = 0;
    } else {
        np->balancefactor = 1;
        right->balancefactor = 0;
    }

    rightleft->balancefactor = 0;

    return rightleft;
}

void
rebalanceAVL(AVL *avl, Node *np, int balance){
	while(np){
		balance += np->balancefactor;

		if(balance == 0)
			return;

		if(balance == -2){
			if(np->right->balancefactor == -1)
				rotateleft(avl, np);
			else
				rotaterightleft(avl, np);
			return;
		}

		if(balance == 2){
			if(np->left->balancefactor == 1)
				rotateright(avl, np);
			else
				rotateleftright(avl, np);
			return;
		}

		Node *parent = np->parent;
		if(parent)
			balance = parent->left == np ? 1 : -1;
		np = parent;
	}
}

void
insert(AVL *avl, keyT key, valueT value){
	Node *prev;
	Node *np = avl->root;
	int cmp;

	if(!np){
		avl->root = newNode(key, value, NULL);
		avl->size++;
		return;
	}

	while(np){
		cmp = strcmp(key, np->key);
		prev = np;
		if(cmp < 0){
			if(np->left == NULL){
				np->left = newNode(key, value, np);
				rebalanceAVL(avl, np, 1);
				return;
			}
			np = np->left;
		} else if(cmp > 0){
			if(np->right == NULL){
				np->right = newNode(key, value, np);
				rebalanceAVL(avl, np, -1);
				return;
			}
			np = np->right;
		}
		else
			; /* ignore repeated value */
	}
}

void printrec(Node *np);

void
print(AVL *avl){
    printrec(avl->root);
}

void
printrec(Node *np) {
    if(np){
        printrec(np->left);
        printf("(%s,%s) ", np->key, np->value);
        printrec(np->right);
    }

}

int
main(void){
    AVL *avl = newAVL();

    insert(avl, "a", "1");
    insert(avl, "z", "9");
    insert(avl, "b", "2");
    insert(avl, "y", "8");
    insert(avl, "c", "3");
    insert(avl, "x", "7");
    insert(avl, "d", "4");

    print(avl);

}
