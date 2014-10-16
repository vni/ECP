#include <stdio.h>
#include <setjmp.h>

/* Error handling with Try/Catch in Ansi C */

jmp_buf buf;

banana() {
	printf("in banana\n");
	longjmp(buf, 3); /* longjmp(env, 0) returns 1 to setjmp */
	printf("UNREACHABLE\n");
}

main() {
	switch (setjmp(buf)) {
		case 0: /* try block */
			printf("Lets try banana()\n");
			banana();
			break;
		case 1:
			printf("Catch(1)\n");
			break;
		case 2:
			printf("Catch(2)\n");
			break;
		default: /* default catch handler */
			printf("Catch(...)\n");
			break;
	}
	/*longjmp(buf, 0);*/ /* do not need a loop */
	return 0;
}
