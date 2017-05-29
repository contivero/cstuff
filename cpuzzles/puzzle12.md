The following is a macro implementation of the famous triple xor swap.
```C
#define SWAP(a,b) ((a) ^= (b) ^= (a) ^= (b))
```
What are the potential problems with the above macro?

Answer:
It doesn't work when a and b are the same object. It assigns zero (0) to the
object in that case (as any value XORed with itself is zero).
A safe alternative is:
```C
#define SWAP(a, b) ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))
```
This checks that the addresses of a and b are different before XOR-ing.
