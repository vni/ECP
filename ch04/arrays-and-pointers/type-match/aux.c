#include <stdio.h>

extern int foo_var[];
void aux_foo(void) {
	printf("aux_foo() foo_var[15]=%d\n", foo_var[15]);
	foo_var[15]=10;
	printf("aux_foo() foo_var[15]=%d\n", foo_var[15]);
}
