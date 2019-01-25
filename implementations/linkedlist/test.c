#include <stdio.h>
#include <stdbool.h>
#include "../util.h"
#include "singlylinkedlist.h"

int
main(void) {
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int i;

    List* list = newlist();
    for (i = 0; i < NELEMS(a); i++) {
        insert(list, a[i]);
    }

    printlist(list);

    delete(list, 3);
    printlist(list);

    delete(list, 0);
    printlist(list);

    delete(list, 9);
    printlist(list);

    freelist(list);
}
