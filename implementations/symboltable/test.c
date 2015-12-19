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
    lookup(table, 1, "5", &values[5]);
    lookup(table, 1, "6", &values[6]);
    lookup(table, 1, "7", &values[7]);
    lookup(table, 1, "8", &values[8]);
    lookup(table, 1, "9", &values[9]);
    lookup(table, 1, "10", &values[10]);
    lookup(table, 1, "11", &values[11]);
    lookup(table, 1, "12", &values[12]);
    lookup(table, 1, "13", &values[13]);

	print(table);
    delete(table, "fifth");
    delete(table, "second");
	printf("\n");
	print(table);

    freesymboltable(table);
}
