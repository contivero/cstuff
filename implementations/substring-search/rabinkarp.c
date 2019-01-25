#include <stdlib.h>
#include <string.h>
#include "../util.h"

#define ALPHABET_SIZE 256

/* Las Vegas implementation of Rabin-Karp */
/* For Monte Carlo, remove the strncmp calls */

typedef struct RabinKarp {
	char *pattern; /* only needed for Las Vegas comparison */
	long pathash;  /* pattern hash */
	long Q;        /* large prime */
	int  patlen;   /* pattern length */
	int  alphsize; /* alphabet size */
	long RM;       /* alphsize^(patlen-1) % Q */
} RK;

long
randomprime(void) {
	return 101; /* TODO implement! */
}

RK *
newRK(char *pat, int patlen) {
	RK *rk = xmalloc(sizeof(*rk));
	rk->pattern  = pat;
	rk->patlen   = patlen;
	rk->alphsize = ALPHABET_SIZE;
	rk->Q        = randomprime();
	rk->RM       = 1;

	return rk;
}

void
freeRK(RK *rk) {
	free(rk);
}

long
rkhash(char *key, long Q, int patlen, int alphsize) {
	long h = 0; 

	for (size_t j = 0; j < patlen; j++)
		h = (alphsize*h + key[j]) % Q;

	return h;
}

int
rksearch(RK *rk, char *txt, int txtlen) {
	long thash    = rkhash(txt, rk->Q, rk->patlen, rk->alphsize);
	long phash    = rk->pathash;
	long RM       = rk->alphsize;
	long Q        = rk->Q;
	int  patlen   = rk->patlen;
	int  alphsize = rk->alphsize;
	int i;

	if (phash == thash && strncmp(txt, rk->pattern, rk->patlen) == 0)
		return 0;

	for (i = patlen; i < txtlen; i++) {
		/* remove leading digit, add trailing digit, check for match */
		thash = (thash + Q - RM*txt[i-patlen] % Q) % Q;
		thash = (thash*alphsize + txt[i]) % Q;
		if (phash == thash && strncmp(txt + i-patlen+1, rk->pattern, rk->patlen == 0))
			return i - patlen + 1;
	}

	return txtlen;
}
