What would you expect the following program to print? 
```C
#include <stdio.h>

int
main(void){
    int a = 10;

    switch(a) {
        case 1:
            printf("ONE\n");
            break;
        case 2:
            printf("TWO\n");
            break;
        defalut:
            printf("NONE\n");
    }

    return 0;
}
```
Answer:
Nothing is printed because there is no `default` as a fallback (notice the
slight typo!). No error is issued because `defalut` might be a valid label.
Some ways to detect this would be using syntax highlighting, or when compiling
with gcc, using `-Wswitch-default` when compiling, which would issue a warning
saying "switch missing default case". Using `-Wall` would work too, though the
warning given is different: "label ‘defalut’ defined but not used".
