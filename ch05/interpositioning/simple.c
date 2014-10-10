/*
 * Test function interpositioning in C
 *
 * Just simple interpositioning of the library function strtol
 */

#include <stdio.h>
#include <stdlib.h>

long int strtol(const char *str, char **endptr, int base) {
	printf("[*JK*>] strtol called\n");
	return 42;
}

int main(void) {
	printf("strtol(\"12345\", NULL, 10) = %ld\n", strtol("12345", NULL, 10));
	printf("22 = %d\n", 22);
	return 0;
}
