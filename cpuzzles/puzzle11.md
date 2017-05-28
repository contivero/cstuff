Here is a function that counts the number of bits set in a number.

| Input | Output      |
| ------|:-----------:|
| 0     | 0 (0000000) |
| 5     | 2 (0000101) |
| 7     | 3 (0000111) |

```C
int
countbits (unsigned int x) {
    static unsigned int mask[] =
            { 0x55555555
            , 0x33333333
            , 0x0F0F0F0F
            , 0x00FF00FF
            , 0x0000FFFF
            };

    int i;
    int shift; /* Number of positions to shift to right*/
    for (i = 0, shift = 1; i < 5; i ++, shift *= 2)
        x = (x & mask[i]) + ((x >> shift) & mask[i]);

    return x;
}
```
Find out the logic used in the above program.

Answer:
