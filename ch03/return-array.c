#include <stdio.h>

typedef struct {
	int data[10];
} Array;

void print_array(Array a) {
	int i;
	for (i=0; i<10; i++)
		printf("%d ", a.data[i]);
	printf("\n");
}

Array foo(Array a) {
	a.data[5] = 100;
	return a;
}

int main(void) {
	Array b;
	Array c;
	int i;
	for (i=0; i<10; i++)
		b.data[i] = 10;
	printf("Array b: ");
	print_array(b);
	c = foo(b);
	printf("after foo(): Array b: ");
	print_array(b);
	printf("after foo(): Array c: ");
	print_array(c);
	return 0;
}
