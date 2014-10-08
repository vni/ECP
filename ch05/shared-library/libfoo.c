#include <string.h>
#include <unistd.h>

#include "libfoo.h"

int x_puts(const char *string) {
	unsigned len = strlen(string);
	return write(1, string, len);
}
