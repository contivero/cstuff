#include <stdlib.h>
#include <string.h>

/* Requires no preprocessing, and a constant extra space apart from the text
 * and the pattern. 
 * Worst case: m(n - m + 1)
 * Complexity: O(mn)
 * 2n expected characters comparisons */

int
search(const char *pattern, const char *text, unsigned int pos) {
	char const *p, *q, *t;

	/* move t to pos */
	for (t = text; *t != '\0' && pos; pos--, t++)
		;
	for (; *t != '\0'; t++){
		for(q = t, p = pattern; *q == *p && *p; q++, p++)
			;
		if(*p == '\0')
			return t - text + 1;
	}

	return -1; /* not found */
}

/* Sedgewick's implementation */
/* Requires finding the length of the pattern and text first (makes more sense
 * in a language where strings know their length) */
int
substringsearch(char *pat, char *txt) {
	int j;
	int patlen = strlen(pat);
	int txtlen = strlen(txt);

	for (int i = 0; i <= txtlen - patlen; i++) {
		for (j = 0; j < patlen; j++) {
			if (txt[i+j] != pat[j])
				break;
		}
		if (j == patlen)
			return i; /* found at the i-th position */
	}

	return -1; /* not found */
}
