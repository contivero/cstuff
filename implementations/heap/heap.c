#include <math.h>

#define MAX(x,y,z) x > y? (x > z? x : z) : (y > z? y : z)

inline int
right(int i){
	return 2*(i + 1);
}

inline int
left(int i){
	return 2*i + 1;
}

inline int
parent(int i){
	return floor(i-1/2.0);
}

void
heapify(int *a, int i, int len){
	int r, l, m, temp;

	r = right(i);
	l = left(i);
	if(r > len && l > len)
		return;

	if(a[r] > a[l])
		m = r;
	else
		m = l;

	if(a[i] == a[m])
		return;

	temp = a[i];
	a[i] = a[m];
	a[m] = temp;

	heapify(a, m, len);
}

void
buildheap(int *a, int len){
	int i;

	for(i = len / 2 - 1; i >= 0; i--)
		heapify(a, i, len);
}

void
heapsort(int *a, int len){
	for( ; len; len--){
		buildheap(a, len);
		int temp = a[0];
		a[0]     = a[len-1];
		a[len-1] = temp;
	}
}

int
removefirst(int *a, int len){

}

void
insert(int *a, int element){

}
