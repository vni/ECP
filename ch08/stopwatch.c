#include <stdio.h>

#define X )*2+1
#define _ )*2
#define s ((((((((((((((((0

static unsigned short stopwatch[] = {
	s _ _ _ _ _ X X X X X _ _ _ X X _,
	s _ _ _ X X X X X X X X X _ X X X,
	s _ _ X X X _ _ _ _ _ X X X _ X X,
	s _ X X _ _ _ _ _ _ _ _ _ X X _ _,
	s _ X X _ _ _ _ _ _ _ _ _ X X _ _,
	s X X _ _ _ _ _ _ _ _ _ _ _ X X _,
	s X X _ _ _ _ _ _ _ _ _ _ _ X X _,
	s X X _ X X X X X _ _ _ _ _ X X _,
	s X X _ _ _ _ _ X _ _ _ _ _ X X _,
	s X X _ _ _ _ _ X _ _ _ _ _ X X _,
	s _ X X _ _ _ _ X _ _ _ _ X X _ _,
	s _ X X _ _ _ _ X _ _ _ _ X X _ _,
	s _ _ X X X _ _ _ _ _ X X X _ _ _,
	s _ _ _ X X X X X X X X X _ _ _ _,
	s _ _ _ _ _ X X X X X _ _ _ _ _ _,
	s _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main(void) {
	int i;
	printf("static unsigned short stopwatch[] = {\n");
	for (i = 0; i < ARRAY_SIZE(stopwatch); i++)
		printf("\t0x%04X,\n", stopwatch[i]);
	printf("};\n");
	printf("\n\nImage:\n");
	for (i = 0; i < ARRAY_SIZE(stopwatch); i++) {
		int j = 16;
		while (j--) {
			putchar(' ');
			if (stopwatch[i] & (1 << j))
				putchar('X');
			else
				putchar('_');
		}
		putchar('\n');
	}
	return 0;
}
