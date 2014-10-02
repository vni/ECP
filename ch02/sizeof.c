#include <stdio.h>

#define N 10

int main(void) {
	unsigned p;
	char *q = NULL;
	p = N * sizeof * q;

	printf("p = N * sizeof * q\np = %u\n", p);
	return 0;
}
