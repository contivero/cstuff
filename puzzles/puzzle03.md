Why does the following C program segfault on IA-64, but not on IA-32?
```C
int
main(void){
	int *p;
	p  = (int *) malloc(sizeof(int));
	*p = 10;
	return 0;
}
```
## Answer
The `(int*)` cast hides the fact that without `#include <stdlib.h>`, the return
type of malloc is assumed to be int. IA-64 happens to have `sizeof(int) < sizeof(int *)`,
which makes this problem obvious.  
__You should never cast the return from malloc!__
* It's unnecessary: `void *` is automatically and safely promoted to any other pointer type in this case.
* If you forget to include `<stdlib.h>`, it can hide the error.
* Clutters the code.
* Makes you repeat yourself.

See: 
* [comp.lang.c FAQ](http://c-faq.com/malloc/mallocnocast.html)
* [Do I cast the return of malloc?](http://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc)
