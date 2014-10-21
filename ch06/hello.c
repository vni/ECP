#include <stdio.h>

/*
 * hello.c
 *                          ls -l       size: text    data    bss    total
 * simple hello world:       7131              877     256      8     1141
 * uninitialized global:     7154              877     256   4032     5165
 * initialized global:      11198              877    4280      8     5165
 * uninitialized local:     11218              909    4280      8     5197
 * initialized local:       11218              989    4280      8     5277
 * -ggdb3:                  28838              989    4280      8     5277
 * -O3 (w/o -ggdb3):        11218              909    4280      8     5197
 */

int global[1000] = { 1, 2, 3, 4, 5, 6 };

int foo(void) {
	int local[1000] = { 100, 200, 100, 300, 400 };
	return local[3];
}

int main(void) {
	printf("Hello, World!\n");
	return foo();
}
