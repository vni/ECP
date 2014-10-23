#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <setjmp.h>

/* NOTE1:
 * Failed to make this code work because of
 * printf("%s() Caught %d signal\n", signum);
 * note: printf expects 2 additional args, but I have put
 * only one. So, signum were treated as a string and
 * when I try to dereference it (at address 2) I got 
 * SEGMENTATION VIOLATION error */

/* NOTE2:
 * used sigsetjmp/siglongjmp here cause setjmp/longjmp
 * forgets setlet previously signals. */

static sigjmp_buf jmphere;

static void inthandler(int signum) {
	printf("%s() Caught %d signal\n", __FUNCTION__, signum);
	longjmp(jmphere, 2);
	exit(13);
}

int main(void) {
	if (signal(SIGINT, inthandler) == (void (*)(int))-1) {
		printf("Error: failed to set SIGINT handler: %s\n", strerror(errno));
		exit(1);
	}

	sigsetjmp(jmphere, SIGINT);

	/* Will exit if after 2 seconds no SIGINT will occur */
	sleep(2);

	return 0;
}
