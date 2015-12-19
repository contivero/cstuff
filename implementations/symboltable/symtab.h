#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct Symtab Symtab;

/* lookup with optional insertion */
void   *lookup(Symtab *table, int insert, char *key, void *value);

void   print(Symtab *table);
int    delete(Symtab *table, char *key);

int    contains(Symtab *table, char *key);
Symtab *newsymboltable(void);
void   freesymboltable(Symtab *table);

typedef void (*symtabfnT)(char *key, void *value, void * clientData);
void mapsymtab(symtabfnT fn, Symtab *table, void *clientData);
