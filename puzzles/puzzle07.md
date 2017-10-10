```C
#include <stdio.h>

#define f(a,b) a##b
#define g(a)   #a
#define h(a)   g(a)

int 
main(void){
	printf("%s\n", h(f(1,2)));
	printf("%s\n", g(f(1,2)));
	return 0;
}
```
At first sight, one would expect both printf calls to output the same, but the result is:
```
12
f(1,2)
```
Why?

## Answer
The `##` preprocessor operator concatenates two tokens together.  
`f(1,2)` becomes `1##2`, which becomes `12`.  
The `#` operator by itself _stringifies_ tokens, so `#a` becomes `"a"`.  
Therefore, `g(f(1,2))` end ups becoming `"f(1,2)"`.  
`h(f(1,2))` is the same as `#(1##2)`, which becomes `#12`, and finally `"12"`.
