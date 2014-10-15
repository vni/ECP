#include <stdio.h>
#include <stdlib.h>

static int bss[1000];
static int data[1000] = { 1, 2, 3, 4 };

/*
 * On my i386 Linux machine
 *
 * virtual memory address space maps something like below
 * (but stack is actually starts at lower address)
 *
 * 0xC0000000 STACK
 *
 * ^^^^^^^^^^
 * .......... HEAP
 * .......... BSS
 * .......... DATA
 * 0x08048000 TEXT
 * 0x00000000 UNMAPPED AREA
 */

int main(int argc, char *argv[]) {
	int a = 13666;
	int *heap = malloc(sizeof(int)*40);
	int *sp = &a;
	printf("STACK %p\n", sp);
	printf(" HEAP %p\n", heap);
	printf("  BSS %p\n", bss);
	printf(" DATA %p\n", data);
	printf(" TEXT %p\n", main);
	printf("\n");
	printf("argc=%d, &argc=%p\n", argc, &argc);
	printf("argv=%p, &argv=%p\n", argv, &argv);

	while (sp) {
		printf("SP(%p)=%u (%08X)\n", sp, *sp, *sp);
		sp++;
	}
	return 0;
}
