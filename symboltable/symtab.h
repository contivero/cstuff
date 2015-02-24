typedef struct Symtab Symtab;

Symtab * newsymboltable(void);
void freesymboltable(Symtab *table);
void * lookup(Symtab *table, int insert, char *key, void *value);

typedef void (*symtabfnT)(char *key, void *value, void * clientData);
void mapsymtab(symtabfnT fn, Symtab *table, void *clientData);
