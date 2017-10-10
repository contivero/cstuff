The following is the offset macros which is used many a times. Figure out what
is it trying to do and what is the advantage of using it.
```C
#define offsetof(st, m) ((size_t)&(((st*)0)->m))
```

## Answer
TODO
