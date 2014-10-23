#include <stdio.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <sys/types.h>

/* NOTE: to exit program hit Ctrl+\ (SIGQUIT) */

static sigjmp_buf jmpbuf;

static void sighndlr(int signum) {
	switch (signum) {
		case SIGINT:
			printf("SIGINT received\n");
			siglongjmp(jmpbuf, SIGINT);
			break;
		case SIGBUS:
			printf("SIGBUS received\n");
			siglongjmp(jmpbuf, SIGBUS);
			break;
		case SIGSEGV:
			printf("SIGSEGV received\n");
			siglongjmp(jmpbuf, SIGSEGV);
			break;
		case SIGILL:
			printf("SIGILL received\n");
			siglongjmp(jmpbuf, SIGILL);
			break;
	}
}

static void die_if(int cond, const char *fmt, ...) {
	if (cond) {
		va_list ap;
		va_start(ap, fmt);
		vfprintf(stderr, fmt, ap);
		va_end(ap);
		exit(13);
	}
}

int main(void) {
	int r;

	r = (int)signal(SIGINT, sighndlr);
	die_if(r == -1, "ERROR: Failed to set SIGINT handler\n");
	r = (int)signal(SIGSEGV, sighndlr);
	die_if(r == -1, "ERROR: Failed to set SIGSEGV handler\n");
	r = (int)signal(SIGBUS, sighndlr);
	die_if(r == -1, "ERROR: Failed to set SIGBUS handler\n");
	r = (int)signal(SIGILL, sighndlr);
	die_if(r == -1, "ERROR: Failed to set SIGILL handler\n");

	if ((r = sigsetjmp(jmpbuf, SIGINT|SIGBUS|SIGSEGV|SIGILL)) == 0) { /* TRY block */
		printf("pid %d\n", getpid());
		/* cause SIGSEGV */
		int *p = 0;
		*p = 17;

again:
		while (1)
			sleep(1);
	} else { /* CATCH block */
		switch (r) {
			case SIGINT:
				printf("SIGINT exception catched\n");
				break;
			case SIGSEGV:
				printf("SIGSEGV exception catched\n");
				break;
			case SIGBUS:
				printf("SIGBUS exception catched\n");
				break;
			case SIGILL:
				printf("SIGILL exception catched\n");
				break;
			default:
				printf("UNSPECIFIED exception catched (%d)\n", r);
				break;
		}
		goto again;
	}

	return 0;
}
