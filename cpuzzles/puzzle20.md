Why is the output of the following program not 20?
```C
#include <stdio.h>

int
main(void) {
    int a = 1;

    switch(a) {
        int b = 20;
        case 1:  printf("b is %d\n", b);
                 break;
        default: printf("b is %d\n", b);
                 break;
    }

    return 0;
}
```

## Answer
The output is garbage, because the switch jumps directly to the appropriate
case (`1` in this example, `default` if no case applies), and the statement
`int b = 20;` is never reached. By default, GCC (7.1.1) properly warns about
non-executed code, while Clang (4.0.1) with `-Wall` warns about usage of an
uninitialized variable.
