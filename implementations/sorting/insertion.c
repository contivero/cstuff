#include <stdlib.h>

void
insertion_sort(int a[], size_t size) {
	if (size == 0 || size == 1) {
		return;
	}

	int tmp;
	for (size_t curr = 1; curr < size; curr++) {
		for (size_t j = curr; j > 0 && a[j-1] > a[j]; j--) {
			tmp    = a[j-1];
			a[j-1] = a[j];
			a[j]   = tmp;
		}
	}
}
