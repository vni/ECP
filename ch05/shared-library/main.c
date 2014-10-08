#include <stdio.h>
#include "libfoo.h"

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
