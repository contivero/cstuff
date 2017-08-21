Another implementation of countbits. Verify whether it is correct (how do you that?).
If so, find out the logic used.
```C
int
countbits(unsigned int x) {
    int count = 0;

    while(x) {
        count++;
        x = x & (x-1);
    }

    return count;
}
```
## Answer:

`x & (x-1)` is a way of turning off the rightmost bit of a value.
For example, take `x = 251`, and then `x = 1024`.

| Expression | Value | Binary representation |
| -----------|:-----:|:---------------------:|
| x          | 251   | 011111011             |
| (x-1)      | 250   | 011111010             |
| x & (x-1)  | 250   | 011111010             |
| x          | 1024  | 100000000             |
| (x-1)      | 1023  | 011111111             |
| x & (x-1)  | 0     | 000000000             |

Thus, if `x = 0`, then the `while` condition is false, and the function
(correctly) returns `0`. Otherwise, `count` is increased, a single bit is turned
off, and the loop goes on until every bit is turned off, and the variable `count`
reflects the amount of one bits the value had.

A way to verify the correctness is stating what was described in the previous
paragraph formally, giving it mathematical rigor.

Another way would be to the function's output to that of another function we
know to be valid, say `valid_countbits()`. Then, we loop from `0` to `UINT_MAX`,
checking that `countbits(i) == valid_countbits(i)` (being careful not to enter
into an infinite loop). This would take too long for a single computer to be
feasible, but could be done in a sensible time using distributed computing. If
for every input, the function gives the same output, then both functions are
mathematically equal.
