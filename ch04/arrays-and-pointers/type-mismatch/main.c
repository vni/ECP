#include <stdio.h>

int foo_var[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
void main_foo(void) {
	printf("main_foo() foo_var[3]=%d\n", foo_var[3]);
	foo_var[3]=100;
	printf("main_foo() foo_var[3]=%d\n", foo_var[3]);
}

int main(void) {
	void aux_foo(void);

	main_foo();
	aux_foo();

	return 0;
}
