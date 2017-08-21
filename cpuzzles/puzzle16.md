What is the use of the following macro?
```C
#define DPRINTF(x) printf("%s:%d\n",#x,x)
```
## Answer
It can be used for debugging, as it prints the name of a variable, followed by
its' numerical value.
