/*
 * C interpositioning example found at
 * https://isisblogs.poly.edu/2011/04/04/simple-intro-to-interposition-in-c/
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(void) {
	printf("calling socket\n");
	return socket(PF_UNIX, SOCK_STREAM, 3);
}
