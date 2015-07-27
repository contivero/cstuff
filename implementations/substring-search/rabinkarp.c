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
	int M;         /* pattern length */
	int R;         /* alphabet size */
	long RM;       /* R^(M-1) % Q */
} RK;

long
randomprime(void){
	return 101; /* TODO implement! */
}

RK *
newRK(char *pat, int patlen){
	RK *rk = xmalloc(sizeof(*rk));
	rk->pattern = pat;
	rk->M  = patlen;
	rk->R  = ALPHABET_SIZE;
	rk->Q  = randomprime();
	rk->RM = 1;

	return rk;
}

void
freeRK(RK *rk){
	free(rk);
}

int
check(int i){
	return 1; /* Monte Carlo implementation */
}             /* For Las Vegas, compare pat vs txt[i..i-M+1] */

long
rkhash(char *key, long Q, int M, int R){
	long h = 0; 
	int j;

	for(j = 0; j < M; j++)
		h = (R*h + key[j]) % Q;

	return h;
}

int
rksearch(RK *rk, char *txt, int txtlen){
	long thash = rkhash(txt, rk->Q, rk->M, rk->R);
	long phash = rk->pathash;
	long RM = rk->R;
	long Q  = rk->Q;
	int  M  = rk->M;
	int  R  = rk->R;
	int i;

	if(phash == thash && strncmp(txt, rk->pattern, rk->M) == 0)
		return 0;

	for(i = M; i < txtlen; i++){
		/* remove leading digit, add trailing digit, check for match */
		thash = (thash + Q - RM*txt[i-M] % Q) % Q;
		thash = (thash*R + txt[i]) % Q;
		if(phash == thash && strncmp(txt + i-M+1, rk->pattern, rk->M == 0))
			return i - M + 1;
	}

	return txtlen;
}
