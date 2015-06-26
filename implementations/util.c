#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void *
xmalloc(size_t size) {
	void *p = malloc(size);

	if(!p)
		die("Out of memory: could not malloc() %d bytes\n", size);

	return p;
}

void *
xcalloc(size_t nmemb, size_t size) {
	void *p = calloc(nmemb, size);

	if(!p)
		die("Out of memory: could not calloc() %d bytes\n", nmemb*size);

	return p;
}

void *
xrealloc(void *p, size_t len) {
	if((p = realloc(p, len)) == NULL)
		die("Out of memory: could not realloc() %d bytes\n", len);

	return p;
}

void
die(const char *errstr, ...) {
	va_list ap;

	va_start(ap, errstr);
	vfprintf(stderr, errstr, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void
warn(const char *warnstr, ...){
	va_list ap;

	va_start(ap, warnstr);
	vfprintf(stderr, warnstr, ap);
	va_end(ap);
}

/* From "The Pragmatic Programmer", page 121
 *
 * Check a line of code's return value
 * If it differs from the expected, print the file and
 * line where the error occurred, then exit
 */
#define CHECK(LINE, EXPECTED_VALUE)	 \
  { int rc = LINE;					  \
	if(rc != EXPECTED_VALUE)			\
		ut_abort(__FILE__, __LINE__, #LINE, rc, EXPECTED_VALUE); }

void
ut_abort(char *file, int ln, char *line, int rc, int exp){
	fprintf(stderr, "%s line %d\n'%s': expected %d, got %d\n", file, ln, line, exp, rc);
	exit(EXIT_FAILURE);
}
