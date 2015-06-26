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
Answer:  
All arrays that are function arguments are rewritten by the compiler at
compiletime into pointers. Therefore, you are basically taking the size of a
pointer to the first element of the array, not the size of the whole array.  
So, depending on the architecture, it will be most likely be 4 or 8.  

Reference:
* Expert C programming, by Peter Van Der Linden (pages 246-49) has some good explanations why this is so.
