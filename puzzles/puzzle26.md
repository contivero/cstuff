Why does the following program give a warning? (remember that sending a normal
pointer to a function requiring const pointer does not give any warning)
```C
#include <stdio.h>
#include <stdlib.h>

void foo(const char **p) { }

int
main(int argc, char **argv) {
    foo(argv);

    return EXIT_SUCCESS;
}
```

## Answer
TODO
