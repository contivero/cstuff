#include <setjmp.h>
#include <stdio.h>

jmp_buf buf;

void
banana(void) {
    printf("in banana()\n");
    longjmp(buf, 1);
    /*NOT REACHED */
    printf("you'll never see this");
}

int
main(void) {
    if (setjmp(buf))
        printf("back in main\n");
    else {
        printf("first time through\n");
        banana();
    }
}
