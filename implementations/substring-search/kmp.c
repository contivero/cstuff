#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util.h"

#define ROWS 256

/* The insight of the KMP algorithm is that we can decide ahead of time exactly
 * how to restart the search, because that decision depends only on the pattern
 */

/* DFA version */

typedef struct KMP {
	char *pattern;
	int *dfa;
} KMP;

static KMP *newKMP(char *pat);
static void freeKMP(KMP *kmp);

KMP *
newKMP(char *pat) {
	int X, j, c;
	KMP *kmp = xmalloc(sizeof(*kmp));
	kmp->pattern = pat;
	int patternlen = strlen(pat); 
	int *dfa;

	kmp->dfa = dfa = xmalloc(ROWS * patternlen * sizeof(*kmp->dfa));
	dfa[pat[0]] = 1;
	for (X = 0, j = 1; j < patternlen; j++) {
		for (c = 0; c < ROWS; c++)
			dfa[c + j*ROWS] = dfa[c + X*ROWS]; /* copy mismatch cases */
		dfa[pat[j] + j*ROWS] = j + 1;          /* set match cases */
		X = dfa[pat[j] + X*ROWS];              /* update restart state */
	}

	return kmp;
}

void
freeKMP(KMP *kmp) {
	free(kmp->dfa);
	free(kmp);
}

int
kmpsearch(char *pat, char *txt) {
	KMP *kmp = newKMP(pat);
	int *dfa = kmp->dfa;
	int i, j;

	for (i = 0, j = 0; txt[i] != '\0' && pat[j] != '\0'; i++)
		j = dfa[txt[i] + j*ROWS];

	return pat[j] == '\0' ? i - j : i;
}

int
main(void){
	printf("%d\n", kmpsearch("ABRACADABRA", "AAABRACADABA"));
	return 0;
}
