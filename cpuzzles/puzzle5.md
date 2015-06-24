Are the following two function prototypes same?
```C
int foobar(void);
int foobar();
```
The following programs should be help in finding the answer.  
Program 1:
```C
#include <stdio.h>

void 
foobar1(void){
	printf("In foobar1\n");
}

void 
foobar2(){
	printf("In foobar2\n");
}

int
main(void){
	foobar1();
	foobar2(33, 'a');
	return 0;
}
```
Program 2:
```C
#include <stdio.h>

void foobar1(void){
	printf("In foobar1\n");
}

void 
foobar2(){
	printf("In foobar2\n");
}

int 
main(void){
	foobar1(33, 'a');
	foobar2();
	return 0;
}
```
Specifying the parameter list as `void` is the correct way of saying "no
parameters" in C. Leaving it empty means variable arguments (i.e. the function
can take any number of parameters of unknown type).  
*Always use void when the function takes no arguments so the compiler detect the error!*
