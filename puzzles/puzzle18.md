What's the output of the following program and why?
```C
int
main(void) {
    float a = 12.5;
    printf("%d\n", a);
    printf("%d\n", *(int *)&a);
    return 0;
}
```

## Answer
For starters, `%d` expects an `int`, but `a` is of type `float`. What happens
then with that value is _undefined behavior_. The following discussion is
therefore implementation dependent.

My laptop is little-endian, has 4-byte ints and floats, and 8 byte doubles, and
uses IEEE floating-point representation. The output when compiled using `gcc
-m32` to generate code for 32-bit ABI is consistently:
```
0
1095237632
```
Floats (single precision numbers) are represented as: [sign bit] [7 exponent bits] [23 mantissa bits]

| `float `| Binary representation             | `int`      |
| --------|:---------------------------------:|:----------:|
| 12.5    | 0 10000010 10010000000000000000000| 1095237632 |

When doing `printf("%d\n", a)`, `a` is promoted to double, and `printf` receives
the following 8 bytes: 00 00 00 00 00 00 29 40. `printf` reads the next four
bytes from the argument list, expecting an `int` to be there (because `%d` was
used). These are: 00 00 00 00. Hence, the `0` value.

When compiled without the `-m32` flag, it generates code for 64-bit ABI. Then,
the output is:
```
-1594945520
1095237632
```
where the first number keeps changing with each run, and the second one is
constant throughout. The first value is a pointer (randomised by ASLR), since
register passing is used on x86-64, so the double is stored into a floating
point register, but `%d` reads from a different register.

References:
* https://bytes.com/topic/c/answers/730534-printf-d-float
* https://news.ycombinator.com/item?id=9766981
