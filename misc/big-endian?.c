#include <stdio.h>

int main(void) {
	int v = 0x11223344;
	char *p = (char *)&v;
	if (*p == 0x11) {
		return 0; /* Big-Endian: return TRUE to the shell */
	} else if (*p == 0x44) {
		return 1; /* Little-Endian: return FALSE */
	} else {
		fprintf(stderr, "OOPS, *p = 0x%02x. System nor big nor little endian.\n", *p);
		return 13;
	}
}
