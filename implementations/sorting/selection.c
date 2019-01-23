#include <stdlib.h>

void
selection_sort(int a[], size_t size) {
	if (size == 0 || size == 1) {
		return;
	}

	size_t j;
	for (size_t curr = 0; curr < size - 1; curr++) {
		int smallest = curr;
		for (j = curr + 1; j < size; j++) {
			if (a[smallest] > a[j]) {
				smallest = j;
			}
		}
		if (smallest != j) {
			int tmp     = a[curr];
			a[curr]     = a[smallest];
			a[smallest] = tmp;
		}
	}
}
