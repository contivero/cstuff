What's the output of the following program and why?
```C
#include <stdio.h>

#define SIZE 10

void 
size(int arr[SIZE]){
	printf("size of array is:%d\n",sizeof(arr));
}

int 
main(void){
	int arr[SIZE];
	size(arr);
	return 0;
}
```
Depending on the architecture it will be 4 or 8.  
The reason is that when a function parameter is an array, the C compiler
interprets it as a pointer, so you are basically taking the size of a pointer
to the first element of the array, not the size of the whole array.
