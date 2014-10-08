#include <stdio.h>
#include "libfoo.h"

/*
 * gcc -c libfoo.c
 * gcc -c main.c
 * ar rcs libfoo.a libfoo.o
 * gcc main.o -lfoo -L.
 */

/*
 * libfoo driver
 */

int main(int argc, char *argv[]) {
	while (*++argv) {
		x_puts(*argv);
		printf("\n");
	}
	return 0;
}
