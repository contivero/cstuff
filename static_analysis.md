Notes on C Static Analysis Tools
===

Summary of some free static analysis tools for C. Usage information lets one get
started with the fast, but some of them provide a wide array of flags or
options.

### [Flawfinder](https://www.dwheeler.com/flawfinder/)
usage: `flawfinder <filename.c>`

### [Clang's "scan-build"](https://clang-analyzer.llvm.org/scan-build.html)
usage: `scan-build make`

To force a rebuild, use: `scan-build make -B`

### [Sparse - Semantic Parser for C](https://sparse.wiki.kernel.org/index.php/Main_Page)
Designed to find possible coding faults in the Linux kernel.

usage: `sparse <filename.c>`

### [RATS - Rough Auditing Tool for Security](https://security.web.cern.ch/security/recommendations/en/codetools/rats.shtml)
usage: `rats -w 3 <filename.c>`

To stick to high priority warnings (less false positives), use `-w 1`.

### [Smatch - The Source Matcher](http://smatch.sourceforge.net)
usage: `smatch --two-passes <filename.c>`

### [Cobra](http://spinroot.com/cobra/)
Developed at NASA's Jet Propulsion Laboratory late 2015, and released for
distribution in September 2016.

usage: `cobra -cpp -f basic <filename.c>`

### [Splint - Secure Programming Lint](http://www.splint.org/)
Good, although its' lack of proper support for C99 syntax is unfortunate, for
instance the parser chokes with `for` initializations:
```C
for(int i = 0; ...
```
usage : `splint <filename.c>`

### [Uno](https://spinroot.com/uno/)

usage: `uno -w <filename.c>`

The `-w` flag enables the picky mode, which complains about more things.

### [Cppcheck](http://cppcheck.sourceforge.net/)

usage: `cppcheck --enable=all <filename.c>`

### tis-interpreter
TODO

### GCC
The compiler shouldn't be overlooked. My personal collection of flags is:
```
-Wpedantic -Wall -Wextra -Wbad-function-cast -Wcast-align -Wcast-qual
-Wduplicated-branches -Wfloat-equal -Wformat=2 -Wformat-truncation=2
-Wimplicit-fallthrough=4 -Winline -Wlogical-op -Wmaybe-uninitialized
-Wmissing-prototypes -Wnested-externs -Wno-missing-braces
-Wno-missing-field-initializers -Wold-style-definition -Wpointer-arith
-Wredundant-decls -Wrestrict -Wshadow -Wstrict-aliasing=2 -Wstrict-overflow=5
-Wstrict-prototypes -Wswitch-default -Wswitch-enum -Wundef -Wuninitialized
-Wunreachable-code -Wunused-macros -Werror
```
Note that [`-pedantic` was deprecated](https://gcc.gnu.org/gcc-4.8/changes.html)
in favor of `-Wpedantic`.

## See also
https://www.gnu.org/software/hurd/open_issues/code_analysis.html
https://github.com/mre/awesome-static-analysis#cc
