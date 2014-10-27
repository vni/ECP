#include <stdio.h>
/* Check assembly output:
 * gcc -S type-promotion.c */

int main(void) {
	/* No type promotion from float to double for bar() */
	int bar(float x);
	char c1 = 1, c2 = 2;
	float f1 = 1.0f, f2 = 2.0f;
	long long llx = 123456789012345678;

	c1 += c2; /* c1 and c2 first should be converted to int then resulting int should be truncated before putting it into c1 */
	printf("the sum of c1 and c2 is %d\n", c1); /* c1 again implicitly promoted to int */

	f1 = f1 + f2; /* f1 and f2 first should be converted to double, then resulting double should be truncated to float */
	/* NOTE: f1 and f2 is not promoted to double as I expected. Here is asm:
	 * flds	40(%esp)
	 * fadds	36(%esp)
	 * fstps	40(%esp) */
	printf("the sum of f1 and f2 is %f\n", f1); /* f1 again implicitly promoted to double */
	foo(f1);
	bar(f2);

	printf("long long llx = %d\n", llx); /* should be taken only 4 bytes instead of 8 */
	printf("long long llx = %lld\n", llx); /* should be taken all 8 bytes */

	printf("sizeof('A') = %d\n", sizeof('A'));
	printf("'A' = %c\n", 'A'); /* 'A' should be promoted to int */
}

/* type promotion */
int foo(double x) {
	return printf("x is %f\n", x);
}

int bar(float x) {
	return printf("x is %f\n", x);
}
