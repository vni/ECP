#include <stdio.h>

int global[1000] = { 1, 2, 3, 4, 5, 6 };

int foo(void) {
	int local[1000] = { 100, 200, 100, 300, 400 };
	return local[3];
}

int main(void) {
	printf("Hello, World!\n");
	return foo();
}
