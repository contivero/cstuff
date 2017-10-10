What's the mistake in the following code?
```C
#include <stdio.h>

int
main(void) {
    int* ptr1, ptr2;
    ptr1 = malloc(sizeof(int));
    ptr2 = ptr1;
    *ptr2 = 10;
    return 0;
}
```
Answer:
Having the asterisk with the type instead of the variable should be enough of a
code smell. The problem is that ptr2 is not a pointer, but just a plain int.
