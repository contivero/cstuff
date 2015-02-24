#include <stdbool.h>

#ifndef _singly_linked_list_h
#define _singly_linked_list_h

/* node's data type */
typedef int dataT;

typedef struct Node Node;
typedef struct List List;

Node* newnode(dataT data);
void  freenode(Node* nodep);

List* newlist(void);
void  freelist(List* list);
void  insert(List* list, dataT data);
void  insertfirst(List* list, dataT data);
bool  delete(List* list, dataT data);
bool  deletefirst(List* list);
dataT get(List* list, long index);

#endif
