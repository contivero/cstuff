#include <stdio.h>
#include <time.h>

int
main(void){
    printf("The sizeof(time_t) is %d\n", sizeof(time_t));
    time_t t = (1 << 32);
    printf("t = %d\n", t);
}
