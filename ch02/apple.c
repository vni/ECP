#include <stdio.h>

int main(int argc, char *argv[]) {
	int var=4;
	/*int *p=&var;*/
	int p=2;
	unsigned apple=sizeof (int) *p;
	printf("apple=%u\n", apple);
	return 0;
}
