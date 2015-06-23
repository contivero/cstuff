#include "symtab.h"

typedef struct Iterator Iterator;

Iterator *newiterator(Symtab *collection);
int       stepiterator(Iterator *iterator, char **key);
void      freeiterator(Iterator *iterator);
