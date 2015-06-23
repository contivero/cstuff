#include <stdio.h>
#include "symtab.h"

int
main(void){
    Symtab *table = newsymboltable();
    int values[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};

    lookup(table, 1, "first", &values[0]);
    lookup(table, 1, "second", &values[1]);
    lookup(table, 1, "third", &values[2]);
    lookup(table, 1, "fourth", &values[3]);
    lookup(table, 1, "fifth", &values[4]);

    printf("%d ", *(int *)lookup(table, 0, "first", NULL));
    printf("%d ", *(int *)lookup(table, 0, "second", NULL));
    printf("%d ", *(int *)lookup(table, 0, "fourth", NULL));
    printf("%d ", *(int *)lookup(table, 0, "fifth", NULL));
    printf("%d\n", *(int *)lookup(table, 0, "third", NULL));

    freesymboltable(table);
}
