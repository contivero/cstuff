What is the output of the following program?
```C
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void
size(int arr[SIZE]) {
    printf("The array size is: %lu\n", sizeof(arr));
}

int
main(void) {
    int arr[SIZE];
    size(arr);
    return EXIT_SUCCESS;
}
```
## Answer
Whatever the output of `sizeof(int *)` is (usually 4 or 8). When an array is
used as a parameter to a function, it decays into a pointer. GCC (7.1.1)
correctly warns about it:
```
puzzle21.c: In function ‘size’:
puzzle21.c:8:45: warning: ‘sizeof’ on array function parameter ‘arr’ will return size of ‘int *’ [-Wsizeof-array-argument]
     printf("size of array is:%d\n",sizeof(arr));
```
And so does clang:
```
puzzle21.c:8:46: warning: sizeof on array function parameter will return size of 'int *' instead of 'int [10]' [-Wsizeof-array-argument]
    printf("The array size is: %lu\n", sizeof(arr));
```
