/*
 * To create linker map issue
 * gcc -Wl,-M main.c > main.linker.map
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("something...\n");
	return 0;
}
