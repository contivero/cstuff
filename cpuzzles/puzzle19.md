After reading about the comma operator in C, it would seem the following program
is perfectly valid, perfectly valid, but it isn't. What's the problem with it?
```C
#include <stdio.h>

int
main(void) {
    int a = 1,2;
    printf("a: %d\n", a);
    return 0;
}
```

## Answer
The comma `,` in C has two uses: as an operator, and a separator.
In the code example, it acts as a separator, and thus doesn't compile (gcc and
clang complain about an identifier missing).

TODO: add a longer explanation and more references

References:
* http://www.geeksforgeeks.org/comna-in-c-and-c/
