The following C program is split across two files.
What do you expect the output to be, if both files are compiled together and
run?
```C
/* file1.c */
int arr[80];

```
```C
/* file2.c */
#include <stdlib.h>
extern int *arr;

int
main(void) {
  arr[1] = 100;
  return EXIT_SUCCESS;
}
```

## Answer
TODO
