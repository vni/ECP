#include <stdio.h>

int main(void) {
	int j = 100;
	switch (2) {
		int j;
		default:
			/*j=1000;*/
			printf("default j=%d\n", j);
			break;
		case 2:
			j=1002;
			printf("2 j=%d\n", j);
			break;
		case 3:
			j=1003;
			printf("3 j=%d\n", j);
			break;
		case 4:
			j=1004;
			printf("3 j=%d\n", j);
			break;
	}
	printf("main j=%d\n", j);
	return 0;
}
