/* .bss section */
char pear[40];
static double peach;

/* .data section */
int mango = 13;
static long melon = 2001;

main() {
	/* forward decls */
	void *malloc(unsigned);

	int i=3, j, *ip;

	ip = malloc(sizeof(i));
	pear[5]=i;
	peach = 2.0*mango;
}
