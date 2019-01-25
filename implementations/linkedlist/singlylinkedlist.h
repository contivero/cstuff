/* Node's data type */
typedef int dataT;

typedef struct Node Node;
struct Node {
	dataT data;
	Node *next;
};

typedef struct List {
	Node *first;
	Node *last;
	long size;
} List;

List* newlist(void);
void  freelist(List *list);
void  insert(List *list, dataT data);
void  insertfirst(List *list, dataT data);
bool  delete(List *list, dataT data);
bool  deletefirst(List *list);
dataT get(const List *list, size_t index);
void  printlist(const List *list);
