Why doesn't the following code print any values?
```C
#include<stdio.h>

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))

int array[] = {23, 34, 12, 17, 204, 99, 16};

int 
main(void){
	int d;

	for(d = -1; d <= (TOTAL_ELEMENTS-2); d++)
		printf("%d\n",array[d+1]);

	return 0;
}
```
Hint:
>! Possible reference: The C programming language (K & R)
>! 
>! | Necessary knowledge | Page     |
>! | ------------------- |:--------:|
>! | sizeof operator     | 135      |
>! | conversion rules    | 44 & 198 |

Answer:
>! The reason it doesn't print anything is because the condition `d <= (TOTAL_ELEMENTS-2)`
>! is false.  The value of `TOTAL_ELEMENTS` is 7, so why does
>! this happen? The sizeof operator returns an unsigned integer (speciffically, of
>! type `size_t` defined in <stddef.h>), while `d` is a signed int.  Due to
>! conversion rules, the signed int is casted to unsigned. Supposing int is 4
>! bytes, -1 is represented as all ones: 11111111 11111111 11111111 11111111.
>! This interpreted as an unsigned is 4294967295, which is clearly not less or
>! equal than 7.
