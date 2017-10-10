What is the differnce between the following function calls to `scanf`?
(notice the space in the second call; try removing it and observe the behaviour
of the program).
```C
#include <stdio.h>
#include <stdlib.h>

int
main(void) {
    char c;
    scanf("%c", &c);
    printf("%c\n", c);

    scanf(" %c", &c);
    printf("%c\n", c);

    return EXIT_SUCCESS;
}
```
## Answer
TODO

If the space is deleted then after pressing `a` and enter, the program finishes
(because the 2nd echoed character is `'\n'`).

