#define SIZE 65536

int main(void)
{
	char source[SIZE], destination[SIZE];
	int i, j;

	for (i = 0; i < 1000; i++)
		for (j = 0; j < SIZE; j++)
			destination[j] = source[j];
	return 0;
}
