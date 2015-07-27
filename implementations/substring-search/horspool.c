#include <stdlib.h>
#include <string.h>
#include "../util.h"

#define ALPHABET_LEN 256
#define OUTPUT(x) (x)

typedef struct BoyerMooreHorspool{
	int *delta;     /* rightmost occurence of a character */
	int patlen;     /* pattern length */
	char *pattern;
} BMH;

BMH *
newBMH(char *pat, int patlen){
	int i, j, *d1;

	BMH *bmh          = xmalloc(sizeof(*bmh));
	bmh->delta   = d1 = xmalloc(sizeof(*bmh->delta) * ALPHABET_LEN);
	bmh->patlen  = patlen;
	bmh->pattern = pat;

	/* preprocess bad-character rule */
	for(i = 0; i < ALPHABET_LEN; i++)
		d1[i] = patlen;
	for(i = 0; i < patlen - 1; i++)
		d1[pat[i]] = patlen - i - 1;

	return bmh;
}

void
freeBMH(BMH *bmh){
	free(bmh->delta);
	free(bmh);
}

void
bmhsearch(BMH *bmh, char *txt, int txtlen){
	int i = 0;
	char c;
	char *pat  = bmh->pattern;
	int patlen = bmh->patlen;
	int *d     = bmh->delta;

	while(i <= txtlen - patlen){
		c = txt[i + patlen - 1];
		if (pat[patlen - 1] == c && memcmp(pat, txt + i, patlen - 1) == 0) 
			OUTPUT(i);    /* use some output function here! */
		i += d[txt[i]];
	}
}
