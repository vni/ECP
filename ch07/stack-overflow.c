#include <stdio.h>

/* Run out of stack space
 * ulimit -s - see stack limit
 * ulimit -s 100 - set stack limit to 100 kbytes */

void recf(int it) {
	char buf[1<<10]; /* 1KB */
	(void)buf; /* discards compiler warning */
	printf("iteration %d\n", it);
	recf(it+1);
}

int main(void) {
	recf(1);
	return 0;
}
