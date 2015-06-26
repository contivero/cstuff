Why doesn't the following program print "hello-out", but prints "hello-err"?
```C
#include <stdio.h>
#include <unistd.h>

int 
main(void){
	for(;;){
		fprintf(stdout, "hello-out");
		fprintf(stderr, "hello-err");
		sleep(1);
	}
	return 0;
}
```
Answer:  
Output is usually buffered by the system. Depending on how it works, simply
adding a newline character `'\n'` at the end of the string should be sufficient
to flush the contents. Otherwise, you can call `fflush(stdout)` explicitly.  On
the contrary, `stderr` tends not to be buffered, since you want to see errors
immediately.
