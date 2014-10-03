#include <stdio.h>

int main(void) {
	int x=1, y=10, z=0;

	printf("x=%d, y=%d, z=%d\n", x, y, z);
	z = y+++x;
	printf("x=%d, y=%d, z=%d\n", x, y, z);
	x=1, y=10;
	z = ++y+x;
	printf("x=%d, y=%d, z=%d\n", x, y, z);

	return 0;
}
