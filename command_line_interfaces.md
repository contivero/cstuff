Command Line Interfaces
===
The [POSIX Utility Conventions](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html)
is a good starting point.
[GNU Standards for Command Line Interfaces](https://www.gnu.org/prep/standards/html_node/Command_002dLine-Interfaces.html)
might be even better, since it follows the POSIX guidelines, but adds the
`--long-flag` style to command options, so ubiquitous nowadays.
A worthwile read is also [Chapter 10, Section 5 of The Art of Unix
Programming](http://catb.org/~esr/writings/taoup/html/ch10s05.html).

Additionally, consider checking out and using whenever possible those names
listed in [GNU Table of Long Options](https://www.gnu.org/prep/standards/html_node/Option-Table.html).
Sticking to names used by other utilities helps users remember the flags, and
makes it easier for them to guess what the flag does. Of course it's just a
guideline, and one should use whatever name for a flag one feels is appropriate,
as long one has valid reasons as to why not to abide by the usual naming.

Some general recommendations:
* Always support `--help` and `--version`.
* `--help` should either list all available options, or just the most important
  and refer to an appropriate man page if they are too many.
* Support `--` as a separator between options and other arguments.

To follow the POSIX convetions, `getopt()` can be used. It might work, but it's
not perfect:
* It requires including `<unistd.h>`, which is not standard C (POSIX rather).
* In Anselm R. Garbe's words, what's wrong with `getopt()` is [the implementation and the GNU flavor of it](http://lists.suckless.org/dwm/0703/2171.html).
* [The API is far from perfect](http://nullprogram.com/blog/2014/10/12/).

To avoid reinventing the wheel, some possible alternatives to `getopt()` are:
* [arg.h - A suckless alternative to getopt](http://git.suckless.org/sbase/plain/arg.h)
* [A magic getopt](http://www.daemonology.net/blog/2015-12-06-magic-getopt.html)

Additional reference:
- [Answer to What are good habits for designing command line arguments?](https://softwareengineering.stackexchange.com/a/307472)
- http://esr.ibiblio.org/?p=7552#comment-1830197
