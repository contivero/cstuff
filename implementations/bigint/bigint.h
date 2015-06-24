typedef struct Bigint Bigint;

Bigint *newBigint(int i);
Bigint *strtobigint(char *s);
char   *biginttostr(Bigint *n);
