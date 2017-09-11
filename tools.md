Tools
---
These notes mostly follow Ben Klemens' _21st Century C_.
* [Make](#make)
* [Debugging: GDB / LLDB](#)
* [Valgrind](#valgrind)
* [Documentation: Doxygen](#)

## Make

For the filename, both `makefile` and `Makefile` are [POSIX compliant](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html#tag_20_76_13_01).

A barebone example of a makefile is:
```mk
P=program_name
OBJECTS=
CFLAGS= -Wall -O3
LDLIBS=
CC=c99

$(P): $(OBJECTS)
```
As a usual convention, the macro `CC` is used to specify the compiler to use,
`CFLAGS` for the compiler flags, and `LDFLAGS` for the linker flags.  Although
any name would do, these are used following those already defined in make's
[default rules](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html#tag_20_76_13_09).

#### Relevant links
* [POSIX Make](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html)
* http://nullprogram.com/blog/2017/08/20/

## Debugging: GDB / LLDB

## Valgrind
Official site: http://valgrind.org/

Remember to compile with debugging symbols on (i.e. the `-g` flag).

To check for memory leaks: `valgrind --leak-check=full program_name`.
To start the debugger at a first error: `valgrind --db-attach=yes program_name`.
## Documentation: Doxygen

