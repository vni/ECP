/*
 * Test function interpositioning in C
 *
 * A more complex example of interpositioning.
 * My malloc is called from the library function strdup.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *malloc(unsigned int size) {
	printf("[*JK*>] malloc(%u)\n", size);
	return calloc(1, size);
}

int main(void) {
	char buf[] = "2009";
	char *copy = NULL;

	copy = strdup("hello world");
	printf("strdup(\"hello\")=%p, '%s'\n", copy, copy);
	return 0;
}
