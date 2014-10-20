#include <string.h>

#define SIZE 65536

int main(void)
{
	char source[SIZE], destination[SIZE];
	int i;

	for (i = 0; i < 1000; i++)
		memcpy(destination, source, SIZE);
	return 0;
}
