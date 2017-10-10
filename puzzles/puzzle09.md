What's the expected output for the following program and why?
```C
#include <stdbool.h>
#include <stdio.h>

int
main(void) {
    int i = 1;

    do {
        printf("%d\n",i);
        i++;
        if(i < 15)
            continue;
    } while(false);

    return 0;
}
```
Possible reading:
The C programming language (K & R), page 60 (What's the effect of continue statement in a do-while loop?)

## Answer
The output is just 1. One might expect that the continue statement would skip
the do-while condition check, but it doesn't. In a while and do-while,
`continue` causes the test part to be executed immediately. In a for, control
passes to the increment step.
