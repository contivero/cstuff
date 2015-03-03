# cstuff
Simple implementations of different algorithms and data structures in C, mainly
as a personal reference. Mostly based on those found on Eric Robert's book
"Programming abstractions in C".
Whenever memory cannot be allocated, the implementations simply abort the program, so be careful
in the cases such behavior is undesirable.

Below are notes on idioms, conventions, and general recommened practices for C
programming (although many are applicable to other languages).

## Notes on C -  Idioms and conventions
* [Names](#names)
* [Constants to the left](#constants-to-the-left)
* [Allocating memory](#allocating-memory)
* [Function prototypes](#function-prototypes)
* [Concatenating string literals](#concatenating-string-literals)
* [Iterating over lists](#iterating-over-lists)
* [Never use gets()](#never-use-gets)
* [Testing for null pointers](testing-for-null-pointers)
* [References](#references)

#### Names
A name should be informative, concise, memorable, and pronounceable if possible.

Global variables can crop up anywhere in a program, so use names descriptive
enough to remind the reader of their meaning. It's also helpful to include a
brief comment with the declaration of each global.

Local variables used in conventional ways can have very short names. The use of
`i` and `j` for loop indices, `p` and `q` for pointers, and `s` and `t` for strings is so
frequent that there is little profit and perhaps some loss in longer names.

Compare:
```C
for(theElementIndex = 0; theElementIndex < numberOfElements;
       theElementIndex++)
    elementArray[theElementIndex] = theElementIndex;
```
to
```C
for(i = 0; i < nelems; i++)
    elem[i] = i;
```
In summary: **Descriptive names for globals, short names for locals**

Programmers are often encouraged to use long variable names regardless of context.
That is a mistake: clarity is often achieved through brevity.

#### Constants to the left
Since C accepts assignments inside if, for, and while statements, a not so
uncommon source of bugs is mixing a comparison with an assignment:

```C
if(x = 0){...}
```
By keeping constants to the left, the compiler will catch erroneous assignments, and once fixed looks like:
```C
if(0 == x){...}
```

#### Allocating memory
Avoid the following anti-idiom:
```C
T p = malloc(sizeof(struct T)); /* not acceptable */
```
If you happen to forget the `struct`, you will have a memory error (although valgrind
will probably catch it).

When doing that, there is no [single source of truth](http://en.wikipedia.org/wiki/Single_Source_of_Truth) about what the type of `p` is.
In particular, suppose the program evolves to:

```C
New_T p = malloc(sizeof(struct T)); /* actually wrong */
```

Remember: [Don't repeat yourself](http://en.wikipedia.org/wiki/Don%27t_repeat_yourself).
The correct way to write these allocations is:

```C
T p = malloc(sizeof(*p));  /* established C idiom */
```
This code is good because:

* There is a single source of truth about the type of p. If that type changes, the
code adjusts automatically and is still correct.

* If the name of p changes, the compiler will most likely detect the error.

#### Function prototypes
Even though parameter names are optional in a function prototype, well-chosen names
are good documentation, so remember to use them.

#### Concatenating string literals
A feature introduced with ANSI C, is the convention that adjacent string
literals are concatenated into one. For instance:

```C
printf("hello,"
       " world\n");
```
is equivalent to
```C
printf("hello, world\n");
```
Beware of missing commas when initializing a list of strings though, because
the compiler won't issue any warnings, and this can have serious consequences.

#### Pointer declarations
Don't put pointers next to types:
```C
Type* p, q; /* misleading, only p is a pointer */
```
The pointer qualifier `*` should be with the variable, not the type.
```C
Type *p, *q; /* correct */
```

#### Never use `gets()`
There is no way to limit the amount of input `gets()` will read. It's an
obsolete function, and `fgets()` should be always used in it's place.

#### Iterating over lists
```C
for(p = listp; p; p = p->next){
  /* do something */
}
```

#### Testing for null pointers
The three usual ways to test a non-null pointer are:
```C
if(p != NULL) ...
if(p != 0) ...
if(p) ...
```
Although mostly a personal taste, one could argue in favor of the first one for
the semantics it conveys. However, it has the downside of depending on the `NULL`
constant expicitly, while the other two don't, making them more portable (Plan
9 for instance, uses `nil` as the null pointer constant instead of `NULL`).
For the sake of portability and conciseness, I prefer the last one.
Analogous reasoning to argue in favor of `!p` when testing for null.

### References
* Brian W. Kernighan and Dennis M. Ritchie, The C Programming Language
* Brian W. Kernighan and Rob Pike, The Practice of Programming
* Peter van der Linden, Expert C Programming: Deep C Secrets
* Eric S. Roberts, Programming abstractions in C
* [suckless.org/style](http://suckless.org/style)
* http://www.cs.tufts.edu/comp/40/idioms.html
