#include <stdio.h>
#include <string.h>

struct {
	char *name;
	union {
		char a[10];
		int i;
		void *p;
	} u;
} st;

int main(void) {
	int *ip = (int *)(st.u.a+1);
	printf("&st.u.i = %p\n", &st.u.i);
	printf("&st.u.a = %p\n", &st.u.a);
	printf("&st.u.a[1] = %p\n", &st.u.a[1]);
	printf("ip = %p\n", ip);

	memset(&st, 0, sizeof(st));

	/* I hope to catch segfault (due to bus error,
	 * due to unalignment memory access) but on my x86
	 * it works well. Need to try it on some RISC */
	*ip = 0x11223344;

	printf("*ip = 0x%08x\n", *ip);
	printf("st.u.i = 0x%08x\n", st.u.i);

	return 0;
}
