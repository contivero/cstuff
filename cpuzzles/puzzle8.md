What is the potential problem with the following code?
```C
#include <stdio.h>

int
main(void){
	char str[80];

	printf("Enter a string:\n");
	scanf("%s", str);
	printf("You entered: %s\n", str);

	return 0;
}
```
Answer:  
Using `scanf` with a simple `%s` is susceptible to a _buffer overflow_.  
An alternative would be using `scanf("%81s", str)`.
