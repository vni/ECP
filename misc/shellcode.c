#include <stdio.h>

/* FIXME: It is not finished. Just a code mess thet shows that
 * rewriting return address is posible */

/*
 * Lets try shell code on modern Linux.
 * Just inspired by Programming Challenge from Chapter 06
 * when students use it.
 */

unsigned char shellcode[] = {
};

/*
 * Stack frame for main() looks something like this:
 * (stack grows downwards)
 *
 * +==================+
 * | ENVIRONMENT VARS |
 * +==================+
 * | ARGS             |
 * +==================+
 * | ARGC             |
 * +==================+
 * | RETURN ADDRESS   |
 * +==================+
 * | LOCAL VARIABLES  |
 * +==================+
 */

int main(int argc, char *argv[]);

void foo(int arg) {
	unsigned long *sp = (unsigned long *)&arg;
	sp--;
	printf("foo &arg=%p\n", &arg);
	printf("foo &sp=%p\n", &sp);
	printf("foo sp=%p, *sp=%p\n", sp, *sp);

	printf("main at 0x%08x\n", main);
	printf("Go back to main\n");

	*sp = (unsigned long)main;
}

void baz(int arg);

void bar(int arg) {
	unsigned long *sp = (unsigned long *)&arg;
	printf("bar() welcomes you!\n");
	sp--;
	*sp = (unsigned long)baz;
	printf("BAR() go back to HELL!\n");
}

void baz(int arg) {
	unsigned long *sp = (unsigned long *)&arg;
	printf("baz() welcomes you!\n");
	sp--;
	*sp = (unsigned long)bar;
	printf("baz() goto bar:\n");
}

int main(int argc, char *argv[]) {
	/*unsigned long *sp = (unsigned long *)&argv[argc]; [> Stack Pointer <]*/
	unsigned long *sp = (unsigned long *)&argc; /* Stack Pointer */
	char **args = argv;

	printf("Welcome to main!\n");
	baz(0);

	printf("&argc=%p, argc=%d\n", &argc, argc);
	while (*args) {
		printf("args=%p, *args='%s'\n", args, *args);
		args++;
	}
	args++; /* skip argv[argc], which is NULL */
	
	/* after *args[] there is environment parameters. Read it. */
	while (*args) {
		printf("envp=%p, *envp='%s'\n", args, *args);
		args++;
	}

	sp--; /* point StackPointer below ARGC. Return address should be there. */
	printf("return address=0x%08X\n", *sp);

	foo(0);

	return 0;
}
