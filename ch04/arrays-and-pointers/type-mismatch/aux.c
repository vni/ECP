#include <stdio.h>

extern int *foo_var;
void aux_foo(void) {
	printf("aux_foo() foo_var[5]=%d\n", foo_var[5]);
	foo_var[5]=10;
	printf("aux_foo() foo_var[5]=%d\n", foo_var[5]);
}
