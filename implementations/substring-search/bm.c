#include <string.h>
#include <stdlib.h>
#include "../util.h"

#define ALPHABET_LEN 256
#define MAX(x,y) (x) > (y) ? (x) : (y)
#define OUTPUT(x) (x)

typedef struct BoyerMoore{
	int *delta1;    /* bad-character shift */
	int *delta2;    /* good suffix shift */
	int patlen;     /* pattern length */
	char *pattern;
} BM;

BM *
newBM(char *pat, int patlen){
	int i, j, *d2, *d1;

	BM *bm          = xmalloc(sizeof(*bm));
	bm->delta1 = d1 = xmalloc(sizeof(*bm->delta1) * ALPHABET_LEN);
	bm->delta2 = d2 = xcalloc(patlen + 1, sizeof(*bm->delta2));
	bm->patlen = patlen;
	bm->pattern = pat;

	/* preprocess bad-character rule */
	for(i = 0; i < ALPHABET_LEN; i++)
		d1[i] = -1;
	for(j = 0; j < patlen; j++)
		d1[pat[j]] = j;

	/* preprocess good suffix rule */
	/* case 1 */
	/* f: starting point of widest border of the suffix of the pattern */
	int *f = xmalloc(sizeof(*f) * (patlen + 1));
	i = patlen;
	j = patlen + 1;
	f[i] = j;
	while(i > 0){
		while(j <= patlen && pat[i-1] != pat[j-1]){
			if (d2[j] == 0)
				d2[j] = j - i;
			j = f[j];
		}
		/* f[i-1] = j - 1; */
		i--; 
		j--;
		f[i] = j;
	}

	/* case 2 */
	j = f[0];
	for (i = 0; i <= patlen; i++){
		if (d2[i] == 0)
			d2[i] = j;
		if (i == j)
			j = f[j];
	}

	return bm;
}

void
freeBM(BM *bm){
	free(bm->delta1);
	free(bm->delta2);
	free(bm);
}

void 
bmsearch(BM *bm, char *txt) {
	int patlen = bm->patlen;
	int txtlen = strlen(txt); /* FIXME */
	int *d1 = bm->delta1;
	int *d2 = bm->delta2;
	char *pat = bm->pattern;

	int i = 0, j;
	while (i <= txtlen - patlen){
		j = patlen - 1;
		while (j >= 0 && pat[j] == txt[i+j]) 
			j--;
		if (j < 0){
			OUTPUT(i);/* function to output character goes here */
			i += d2[0];
		} else {
			i += MAX(d2[j+1], j - d1[txt[i+j]]);
		}
	}
}
