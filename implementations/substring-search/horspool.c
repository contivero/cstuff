#include <stdlib.h>
#include <string.h>
#include "../util.h"

#define ALPHABET_LEN 256
#define OUTPUT(x) (x)

/* Boyer-Moore-Horspool implementation */
typedef struct BoyerMooreHorspool{
	int *delta;    /* rightmost occurence of a character */
	int patlen;    /* pattern length */
	char *pattern;
} BMH;

BMH *
newBMH(char *pat, int patlen){
	int i, j, *d1;

	BMH *bmh        = xmalloc(sizeof(*bmh));
	bmh->delta = d1 = xmalloc(sizeof(*bmh->delta) * ALPHABET_LEN);
	bmh->patlen = patlen;
	bmh->pattern = pat;

	/* preprocess bad-character rule */
	for(i = 0; i < ALPHABET_LEN; i++)
		d1[i] = -1;
	for(j = 0; j < patlen - 1; j++)
		d1[pat[j]] = j;

	return bmh;
}

void
freeBMH(BMH *bmh){
	free(bmh->delta);
	free(bmh);
}

void
bmhsearch(BMH *bmh, char *txt){
	int i = 0, j;
	int txtlen = strlen(txt);
	int patlen = bmh->patlen;
	char *pat = bmh->pattern;
	int *d = bmh->delta;

	while (i <= txtlen - patlen){
		j = patlen - 1;
		while (j >= 0 && pat[j] == txt[i+j])
			j--;
		if (j < 0) 
			OUTPUT(i);
		i += patlen - 1;
		i -= d[txt[i]];
	}
}
