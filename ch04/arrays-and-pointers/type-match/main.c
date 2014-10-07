#include <stdio.h>

int foo_var[100];
void main_foo(void) {
	printf("main_foo() foo_var[15]=%d\n", foo_var[15]);
	foo_var[15]=10;
	printf("main_foo() foo_var[15]=%d\n", foo_var[15]);
}

void init_foo(void) {
	int i;
	for (i=0; i<100; i++)
		foo_var[i]=i*i;
}

int main(void) {
	void aux_foo(void);

	init_foo();
	main_foo();

	init_foo();
	aux_foo();

	return 0;
}
