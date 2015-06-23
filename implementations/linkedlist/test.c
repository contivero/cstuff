#include <stdio.h>
#include "util.h"
#include "singlylinkedlist.h"

int
main(void){
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int i;

    List* list = newlist();
    for(i = 0; i < NELEMS(a); i++){
        insert(list, a[i]);
    }

    Node* np;
    for(np = list->first; np; np = np->next){
        printf("%d ", np->data);
    }
    printf("\n");

    delete(list, 3);
    for(np = list->first; np; np = np->next){
        printf("%d ", np->data);
    }
    printf("\n");

    delete(list, 0);
    for(np = list->first; np; np = np->next){
        printf("%d ", np->data);
    }
    printf("\n");

    delete(list, 9);
    for(np = list->first; np; np = np->next){
        printf("%d ", np->data);
    }
    printf("\n");

    freelist(list);
}
