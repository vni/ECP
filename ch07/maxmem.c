#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int chunks = 0;
	int shift = 20; /* by default allocate 1 Mb chunks */

	if (argc != 1 && argc != 2) {
		fprintf(stderr, "ERROR: Usage: %s [shift]\n", *argv);
		return 1;
	}

	if (argc == 2) {
		shift = atoi(*++argv);
		if (shift < 0 || shift > 31) {
			fprintf(stderr, "ERROR: invalid shift (%d), should be in range 0-31.", shift);
			return 1;
		}
	}

	while (malloc(1 << shift))
		++chunks;
	printf("Allocated %d chunks of %d bytes total\n", chunks, 1 << shift);
	return 0;
}
