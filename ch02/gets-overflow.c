#include <stdio.h>

void foo(void) {
	char buf[4];
	gets(buf);
	printf("buf='%s'\n", buf);
}

int main(void) {
	foo();
	return 0;
}
