Is the above valid C code? If so, what is it trying to achieve and why would
anyone do something like it?
```C
void
duff(register char *to, register char *from, register int count) {
    register int n = (count+7)/8;
    switch(count%8){
    case 0: do{ *to++ = *from++;
    case 7:  *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
            }while( --n >0);
    }
}
```
Answer: See https://en.wikipedia.org/wiki/Duff%27s_device
