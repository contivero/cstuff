What's the output of the following program and why?
```C
#include <stdio.h>

int
main(void){
	float f = 0.0f;
	int i;

	for(i = 0; i < 10; i++)
		f = f + 0.1f;

	if(f == 1.0f)
		printf("f is 1.0 \n");
	else
		printf("f is NOT 1.0\n");

	return 0;
}
```
The reason f is not 1.0 is because the floating-point representation of 0.1 isn't exact.  
The value stored in f is about 0.10000000149011612, so adding it 10 times
doesn't give you 1.0 exactly.

You can check floating point representations [here](http://www.h-schmidt.net/FloatConverter/IEEE754.html).  
A good reading on the subject is: [What Every Computer Scientist Should Know About Floating-Point Arithmetic](http://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html)
