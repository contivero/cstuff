typedef struct List List;

List* newlist(void);
void  freelist(List* list);
void  insert(List* list, dataT data);
void  insertfirst(List* list, dataT data);
int   delete(List* list, dataT data);
int   deletefirst(List* list);
dataT get(List* list, long index);
