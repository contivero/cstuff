#include <stddef.h>

#define NELEMS(array) (sizeof(array)/sizeof(array[0]))

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *p, size_t len);
void die(const char *errstr, ...);
void warn(const char *warnerr, ...);
