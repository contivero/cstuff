#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BYTE_SIZE 8

static void rlcompress(void);
static void rldecompress(void);

/* Simple binary run-length encoding implementation
 * Based from Sedgewick's in "Algorithms"
 */

void
rlcompress(void) {
	int count = 0;
	int old = 0;
	FILE *fp = freopen(NULL, "rb", stdin);
	uint8_t byte, bit;
	int i;

	while (fread(&byte, sizeof(byte), 1, fp)) {
		for (i = 0; i < BYTE_SIZE; i++) {
			bit = byte & (0x80 >> i) ? 1 : 0;
			if (bit != old) {
				putchar(count);
				count = 0;
				old = !old;
			} else if (count == 255) {
				putchar(count);
				count = 0;
				putchar(count);
			}
			count++;
		}
	}
	putchar(count);
}

void
rldecompress(void) {
	uint8_t count;
	uint8_t bit = 0;
	uint8_t byte = 0;
	int i = 0;
	FILE *fp = freopen(NULL, "rb", stdin);

	while (fread(&count, sizeof(count), 1, fp)) {
		for (; count; i++, count--) {
			if (i == 8) {
				putchar(byte);
				byte = 0;
				i = 0;
			}
			if (bit)
				byte |= (0x80 >> i);
		}
		bit = !bit;
	}

	if (bit) {
		while (i != 8)
			byte |= (0x80 >> i++);
	}
	
	putchar(byte);
}

int
main(int argc, char *argv[]) {
	if (argc < 2)
		return EXIT_FAILURE;

	if (strcmp(argv[1], "d") == 0)
		rldecompress();
	else if (strcmp(argv[1], "c") == 0)
		rlcompress();
	else
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
