Can you see a potential problem with the way `error` is defined?
Anything else with the rest of the code?
```C
#include <stdio.h>
#include <stdlib.h>

void
error(char *s) {
    printf(s);
}

int
main(void) {
    int *p = malloc(sizeof(*p));

    if(!p) {
        error("Could not allocate memory. Quitting...\n");
        exit(1);
    }

    /* some code using p */

    return 0;
}
```
## Answer
The biggest issue is that `error` passes the `char *` directly to printf. This
is a security exploit waiting to happen (see: TODO).
The call should be: `printf("%s\n", s);`

Aside from that, `printf` outputs to `stdout`; if we want to inform about an
error, the appropriate would be using `stderr`.

Lastly, `exit(1)` is not portable (in most platforms it means failure, but in
others like OpenVMS) it means success. It would be better to use the standard
macro `EXIT_FAILURE` from `<stdlib.h>`. In contrast, `return 0;` in `main` is
portable, but we might as well use `EXIT_SUCCESS` for consistency and clarity.
