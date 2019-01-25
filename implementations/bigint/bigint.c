#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "bigint.h"
#include "../util.h"

struct Bigint {
	int finaldigit;
	Bigint * leadingdigits;
};

static int    finaldigit(const Bigint *n);
static Bigint *leadingdigits(Bigint *n);
static Bigint *addwithcarry(Bigint *n1, Bigint *n2, int carry);
static Bigint *multiplydigit(int digit, Bigint *n);
static Bigint *digitcons(Bigint *n, int digit);

int
finaldigit(const Bigint *n) {
	return n ? n->finaldigit : 0;
}

Bigint *
leadingdigits(Bigint *n) {
    return n ? n->leadingdigits : n;
}

Bigint *
newbigint(int i) {
	if (i < 0)
		die("Negative integers not permitted\n");
	if (i == 0)
		return NULL;

	return digitcons(newBigint(i/10), i % 10);
}

Bigint *
strtobigint(char *s){
	int len;
	char ch;
	char *t;

	len = strlen(s);
	if (len == 0)
		return NULL;
	ch = s[len-1];
	if (!isdigit(ch))
		die("Illegal digit %c\n", ch);

	t = xmalloc(len - 1);
	strncpy(t, s, len - 2);
	return digitcons(strtobigint(t), ch - '0');
}

char *
biginttostr(Bigint *n){
	char *s = xmalloc(sizeof(*s) * 2);

	s[0] = finaldigit(n) + '0';
	s[1] = '\0';
	if (leadingdigits(n)) {
		/* TODO finish this */
		char *t = biginttostr(leadingdigits(n));
		int len = strlen(t);
		// s = concat(, s);
	}

	return s;
}

Bigint *
addwithcarry(Bigint *n1, Bigint *n2, int carry){
	int sum;
	Bigint *bi1, *bi2;

	bi1 = leadingdigits(n1);
	bi2 = leadingdigits(n2);
	sum = finaldigit(n1) + finaldigit(n2) + carry;
	if (sum == 0 && !bi1 && !bi2)
		return NULL;

	return digitcons(addwithcarry(bi1, bi2, sum/10), sum % 10);
}

Bigint *
addbigint(Bigint *n1, Bigint *n2){
	return addwithcarry(n1, n2, 0);
}

Bigint *
multiplybigint(Bigint *n1, Bigint *n2) {
	if (!n1)
		return NULL;
	Bigint *aux = multiplydigit(finaldigit(n1), n2);
	return addbigint(aux, multiplybigint(leadingdigits(n1), digitcons(n2, 0)));
}

Bigint *
multiplydigit(int digit, Bigint *n) {
	if (!n)
		return NULL;
	return addbigint(n, multiplydigit(digit - 1, n));
}

Bigint *
digitcons(Bigint *leadingdigits, int finaldigit) {
	if (!leadingdigits && finaldigit == 0)
		return NULL;

	Bigint *bp        = xmalloc(sizeof(*bp));
	bp->finaldigit    = finaldigit;
	bp->leadingdigits = leadingdigits;

	return bp;
}
