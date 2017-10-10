What is the output of the following program?
```C
#include <stdio.h>
#include <stdlib.h>

int
main(void) {
    int i = 10;

    printf("i : %d\n", i);
    printf("sizeof(i++) is: %d\n", sizeof(i++));
    printf("i : %d\n", i);

    return EXIT_SUCCESS;
}
```
## Answer
The output on my laptop is:
```
i : 10
sizeof(i++) is: 4
i : 10
```
The value of `i` isn't incremented because TODO.
