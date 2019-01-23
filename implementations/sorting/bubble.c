#include <stdlib.h>

void
bubble_sort(int a[], size_t size) {
	if (size == 0 || size == 1) {
		return;
	}

	int tmp;
	for (size_t curr_limit = size-1; curr_limit > 0; curr_limit--) {
		for (size_t j = 0; j < curr_limit; j++) {
            if (a[j] > a[j+1]) {
                tmp    = a[j+1];
                a[j+1] = a[j];
                a[j]   = tmp;
            }
		}
	}
}
