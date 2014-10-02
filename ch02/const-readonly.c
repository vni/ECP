#include <stdio.h>

int main(void) {
	const int v = 15;
	int *p = &v;
	*p = 10;
	printf("v=%d\n", v);
	return 0;
}
