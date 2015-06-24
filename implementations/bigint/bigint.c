#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "bigint.h"
#include "../util.h"

struct Bigint {
	int finaldigit;
	Bigint * leadingdigits;
};

static Bigint *addwithcarry(Bigint *n1, Bigint *n2, int carry);
static Bigint *multiplydigit(int digit, Bigint *n);
static Bigint *digitcons(Bigint *n, int digit);
static Bigint *leadingdigits(Bigint *n);
static int    finaldigit(Bigint *n);

Bigint *
newbigint(int i){
	if(i < 0)
		die("Negative integers not permitted\n");
	if(i == 0)
		return NULL;

	return digitcons(newBigint(i/10), i % 10);
}

Bigint *
strtobigint(char *s){
	int len;
	char ch;
	char *t;

	len = strlen(s);
	if(len == 0)
		return NULL;
	ch = s[len-1];
	if(!isdigit(ch))
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
	if(leadingdigits(n))
		s = concat(biginttostr(leadingdigits(n)), s);

	return s;
}

Bigint *
addwithcarry(Bigint *n1, Bigint *n2, int carry){
	int sum;
	Bigint *bi1, *bi2;

	bi1 = leadingdigits(n1);
	bi2 = leadingdigits(n2);
	sum = finaldigit(n1) + finaldigit(n2) + carry;
	if(sum == 0 && bi1 == NULL && bi2 == NULL)
		return NULL;

	return digitcons(addwithcarry(bi1, bi2, sum/10), sum % 10);
}

Bigint *
addbigint(Bigint *n1, Bigint *n2){
	return addwithcarry(n1, n2, 0);
}
