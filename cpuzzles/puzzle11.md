What would be the output of the following C program? Is it even valid?
```C
#include <stdio.h>

int
main(void) {
    int i = 43;
    printf("%d\n", printf("%d", printf("%d", i)));
    return 0;
}
```

## Answer

The output is `4321`. `printf` returns the number of characters printed.
First `43` is printed (the value of `i`). Since two bytes were printed, the
rightmost `printf` returns `2`, which is later used by the second `printf`.
Lastly, this `printf` returns `1`, because it only printed one character (`2`).
Thus, the leftmost `printf` takes this `1`, and prints it followed by the
newline character `\n`.
