# cstuff
Simple implementations of different algorithms and data structures in C, mainly
as a personal reference. Some based on those found on Eric Robert's
*Programming abstractions in C*, others in Sedgewick's *Algorithms*.
Whenever memory cannot be allocated, the implementations simply abort the
program, so be careful in the cases such behavior is undesirable.

Below are notes on idioms, conventions, and general recommened practices for C
programming (although many are applicable to other languages). Some stuff is
taken almost verbatim from the references.

## Notes on C - Idioms and conventions
* [Names](#names)
* [Macros](#macros)
  - [Avoid function macros](#avoid-function-macros)
  - [Always parenthesize the macro body and arguments](always-parenthesize-the-macro-body-and-arguments)
* [Allocating memory](#allocating-memory)
  - [Correct use of `sizeof`](#correct-use-of-sizeof)
* [Function prototypes](#function-prototypes)
* [Concatenating string literals](#concatenating-string-literals)
* [Iterating over lists](#iterating-over-lists)
* [Never use gets()](#never-use-gets)
* [Unions for different interpretations of the same data](#unions-for-different-interpretations-of-the-same-data)
* [Testing for null pointers](#testing-for-null-pointers)
* [`enum` vs. `#define`](#enum-vs-define)
* [General Idioms](#general-idioms)
  - [Idiomatic variable names](#idiomatic-variable-names)
  - [Infinite loop](#infinite-loop)
  - [Nesting an assignment inside a loop condition](#nesting-an-assignment-inside-a-loop-condition)
  - [Getting the size of an array](#getting-the-size-of-an-array)
  - [Deleting from an array](#deleting-from-an-array)
* [Parenthesis on sizeof but not on return](#idiomatic-variable-names)
* [Exit codes](#exit-codes)
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
for (theElementIndex = 0; theElementIndex < numberOfElements; theElementIndex++)
    elementArray[theElementIndex] = theElementIndex;
```
to
```C
for (i = 0; i < nelems; i++)
    elem[i] = i;
```
In summary: **Descriptive names for globals, short names for locals**

Programmers are often encouraged to use long variable names regardless of context.
That is a mistake: clarity is often achieved through brevity.

Also, don't use the `_t` suffix for types, nor the `_s` suffix for functions.
The first is reserved for types (typedefs) on the C and POSIX standards, the
second for bounds-checking functions on the Annex K of the C11 standard.

#### Macros
##### Always parenthesize the macro body and arguments
```C
/* Incorrect, nothing parenthesized */
#define square(x) x * x

y = 1 / square(a + b)
```
This yields an incorrect result:
```C
y = 1 / a + b * a + b;
```
Still, if we only parenthesize the arguments:
```C
/* Better, but still incorrect */
#define square(x) (x) * (x)

y = 1 / square(a + b);
```
The result is:
```C
y = 1 / (a + b) * (a + b);
```
We need to parenthesize both body and arguments:
```C
/* Correct */
#define square(x) ((x) * (x))
```
Yielding what was originally expected:
```C
y = 1 / ((a + b) * (a + b));
```
##### Avoid repeating parameters
One serious problem with function macros is that if a parameter appears more
than once in the definition, and the argument used includes an expression with
side effects, those side effects occur more than once, resulting in a subtle
bug, e.g.:
```C
#define islower(c) ((c) >= 'a' && (c) <= 'z')
/* ... */
while(islower(c = getchar()))
    /* ... */;
```
Sometimes this can be easily circumvented, e.g.:
```C
#define islower(c) ((c) - 'a' < 26)
```
Other times, it requires less than ideal workarounds.

Instantiating a macro at every occurrence makes the compiled program larger too.

Still, lowercase function macros tend to be misleading, since it's easy to
confuse them with a normal function. As long as no side effects can occur,
lowercase for macros is fine; uppercase has been conventionally used to
highlight the fact that it's a macro, and is preferable if side effects are
possible.

#### Allocating memory
##### Correct use of `sizeof`
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
T p = malloc(sizeof(*p)); /* established C idiom */
```
This code is good because:

* There is a single source of truth about the type of p. If that type changes, the
code adjusts automatically and is still correct.

* If the name of p changes, the compiler will most likely detect the error.
##### Don't cast the return of malloc and friends
In pre-1989 C, there was no void pointer, and `char *` was used as a generic pointer.
Thus, `malloc()` returned `char *`, and it was common to cast the value to the
appropriate pointer type. However, the type `void *` was added with ANSI C
(C89), and `void *` is automatically promoted. Casting the return of malloc can
even hide a subtle bug if one forgets to `#include <stdlib.h>`. In that case,
the compiler, not seeing malloc's prototype, assumes that it returns an `int`,
and were the cast not present, it would properly warn about an assignment of a
pointer to integer. But using a cast, the warning is silenced (although
compilers are now likely to report missing prototypes for functions in scope).

#### Function prototypes
The purpose of ANSI C prototypes is to reduce mismatches between formal and
actual parameter types, making C a more reliable language.
Even though parameter names are optional in function prototypes, well-chosen names
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
obsolete function, removed from C starting from C11,  and `fgets()` should be
always used in it's place. Alternatively, C11 adds `gets_s` in its' Annex K, but
it is optional (so C11 conforming platforms may not implement it), and the
standard itself recommends sticking to `fgets()`.

#### Iterating over lists
```C
for (p = listp; p; p = p->next){
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
[Jens Gustedt also points out problems with `NULL` on functions taking a variable
number of arguments](https://gustedt.wordpress.com/2010/11/07/dont-use-null/).
For the sake of portability and conciseness, I prefer the last one.
Analogous reasoning to argue in favor of `!p` when testing for null.

#### Unions for different interpretations of the same data
Ignoring this is architecture dependent, here is an example:
```C
union bits32_tag {
    int whole;                         /* 32-bit value */
    struct {char c0, c1, c2, c3} byte; /* four 8-bit values */
} value;
```
This provides a way to extract the full 32-bit value by doing `value.whole`, or
the individual byte fields `value.byte.c0` and so on.

#### Document intentional fallthroughs on cases
Comment cases that fallthrough, so as to leave it explicit. Example:
```C
switch (argc) {
case 2:
        month = estrtonum(argv[0], 1, 12);
        v++;
case 1: /* fallthrough */
        year = estrtonum(argv[0], 0, INT_MAX);
        break;
default:
    usage();
}
```
As of GCC 7, the flag `-Wimplicit-fallthrough` can be used to detect this.

#### `enum` vs. `#define`
Use `enum` for semantically grouped values, `#define` otherwise.
```C
#define MAX_LENGTH 1024
#define MASK       0x7FFFFFFF

enum { NORTH, SOUTH, EAST, WEST };
```
Enums have one advantage: their names usually persist through to the debugger,
and can be used while debugging code; `#define`d names are typically discarded
during compilation.

### General idioms
#### Idiomatic variable names
```C
struct passwd *pw;
FILE *fp;
```
#### Infinite loop
There are two stablished forms, the shortest is
```C
for (;;)
    ...
```
but
```C
while (1)
    ...
```
is also popular. Avoid anything else.

#### Nesting an assignment inside a loop condition
```C
while((ch = getchar()) != EOF)
    putchar(ch);
```

#### Getting the size of an array
The idiomatic way is using `sizeof`, as shown in the following code:
```C
#define NELEMS(array) (sizeof(array)/sizeof(array[0]))

double dbuf[100];

for (size_t i = 0; i < NELEMS(dbuf); i++)
    /* statement */;
```
This is an appropriate use for a macro, because it does something that a
function cannot: compute the size of an array from its declaration.

#### Deleting from an array
The idiom is using memmove (p.68 of [2]), for instance:
```C
memmove(array, array+1, (ARRAY_SZ-1)*sizeof(array[0]));
```
deletes the element `array[0]`, by shifting all the values from `array[1]` to
`array[ARRAY_SZ-1]`, leaving an empty space at the end. Of course, keep in mind
this an _O(n)_ operation.

### Parenthesis on sizeof but not on return
[I'll let Torvalds do the talking:](https://lkml.org/lkml/2012/7/11/103)
> On Wed, Jul 11, 2012 at 1:14 AM, George Spelvin <linux@horizon.com> wrote:
> >
> > Huh.  I prefer sizeof without parens, like I prefer return without parens.
>
> Umm. The two have *nothing* to do with each other.
>
> > It actually annoys me when I see someone write
> >
> >         return(0);
>
> Absolutely. Anybody who does that is just terminally confused.
> "return()" is in no way a function.
>
> But "sizeof()" really *is* a function. It acts exactly like a function
> of it's argument. There is no reason to not treat it that way. Sure,
> the C standard *allows* you to not have parenthesis around an
> expression argument, but you should treat that as the parsing oddity
> it is, nothing more. There is zero reason not to have the parenthesis
> there.
>
> In contrast, "return" can never be part of an expression, and the
> parenthesis never make any sense.
>
> With "return", there's no precedence issues, for example.
>
> With "sizeof()" there are: sizeof(x)+1 is very different from
> sizeof(x+1), and having the parenthesis there make it clearer for
> everybody (sure, you can write the first one as "sizeof x + 1", but
> let's face it, the precedence is way more obvious if you just think of
> sizeof as a function).
>
> Here's an example of a really bad use of "sizeof" that doesn't have
> the parenthesis around the argument: sizeof(*p)->member. Quite
> frankly, if you do this, you should be shot. It makes people have to
> parse the C precedence rules by hand. In contrast, parsing
> sizeof((*p)->member) is *way* easier for humans.
>
> And let's face it: if you write your code so that it's easy to parse
> for a machine, and ignore how easy it is to parse for a human, I don't
> want you writing kernel code. There's a reason we have the coding
> standards. They aren't for the *compiler*. They are for *humans*.
>
> And humans should think of sizeof() as a function, not as some
> ass-backwards special case C parsing rule that is subtle as hell.

### Exit codes

To indicate success when returning from `main()` or using `exit()`, stick to
`EXIT_SUCCESS`. Similarly, use `EXIT_FAILURE` when indicating failure of the
execution. These macros are defined in `<stdlib.h>`, and are the only portable
way to indicate success and failure of execution.  `exit(1)` is plataform
dependent (e.g. OpenVMS uses odd numbers to indicate success, making `exit(1)`
indicate success instead of failure). For consistency, portability, and their
semantics, use the macros.

For anyone wondering what the standard says, the following is from the C11
Standard, although present on the C89 standard (ANSI C) already:
> 5.1.2.2.3 Program termination
>
> If the return type of the **main** function is a type compatible with **int**, a return from the
> initial call to the **main** function is equivalent to calling the **exit** function with the value
> returned by the **main** function as its argument; reaching the **}** that terminates the
> **main** function returns a value of 0.

And then:

> 7.22.4.4 The exit function
> Synopsis
> ```
> #include <stdlib.h>
> _Noreturn void exit(int status);
> ```
>
> [...]
>
> If the value of **status** is zero or **EXIT_SUCCESS**, an implementation-defined form
> of the status _successful termination_ is returned. If the value of **status*** is
> **EXIT_FAILURE**, an implementation-defined form of the status _unsuccessful termination_
> is returned. Otherwise the status returned is implementation-defined.

### References
1. Brian W. Kernighan and Dennis M. Ritchie, The C Programming Language
2. Brian W. Kernighan and Rob Pike, The Practice of Programming
3. Peter van der Linden, Expert C Programming: Deep C Secrets
4. [Eric S. Roberts, Programming Abstractions in C](https://cs.stanford.edu/people/eroberts/books/ProgrammingAbstractionsInC/)
5. [Suckless' Coding Style](http://suckless.org/coding_style)
6. [Idioms for C programmers](http://www.cs.tufts.edu/comp/40/idioms.html)
7. [Linux kernel coding style](https://01.org/linuxgraphics/gfx-docs/drm/process/coding-style.html)
8. Jens Gustedt, Modern C
9. [Ben Klemens, 21st Century C: Tips from the New School (2nd Edition)](http://shop.oreilly.com/product/0636920033677.do)
10. [Steve Summit, comp.lang.c Frequently Asked Questions](http://c-faq.com)

### Addendum
[C Humor](http://www.softpanorama.org/Lang/Cilorama/humor.shtml), because why
not.
