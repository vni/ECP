#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

banana() {
	printf("in banana\n");
	longjmp(buf, 1);
	printf("UNREACHABLE\n");
}

main() {
	if (setjmp(buf)) {
		printf("back in main\n");
	} else {
		printf("Normal execution thread. Before call to banana()\n");
		banana();
	}
	longjmp(buf, 0);
	return 0;
}
