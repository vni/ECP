#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* using brk/sbrk syscalls to do memory manager */

#define MIN_ALLOC 10

static FILE *dbg_output_stream;

static void dbg(const char *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	vfprintf(dbg_output_stream, fmt, va);
	va_end(va);
}

static void trace(const char *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	vfprintf(stdout, fmt, va);
	va_end(va);
}

union hdr {
	double alignment;
	struct {
		union hdr *next;
		size_t size; /* in sizeof(union hdr) byte units */
	} s;
};

static union hdr *free_list;
static union hdr *used_list;

static void mem_dump(void) {
	union hdr *cursor;
	trace(">>> %s()\n", __FUNCTION__);
	if (free_list == NULL) {
		printf("free_list is empty\n");
		return;
	}
	for (cursor = free_list; cursor; cursor = cursor->s.next) {
		trace("**********************\n");
		trace("hdr[%p].size=%u\n", cursor, cursor->s.size);
	}
}

/* return size in units of allocated memory, -1 if failure */
static int get_more_os_mem(size_t units, union hdr **tailp) {
	units = units < MIN_ALLOC ?  MIN_ALLOC : units + 1; /* +1 for header */
	*tailp = sbrk(units*sizeof(union hdr));
	if (*tailp == (void *) -1) {
		dbg("ERROR: can't get more memory from the system\n");
		return -1;
	}
	(**tailp)->s.size = units;
	tmp->s.next = NULL;
	free_list = tmp;
	return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

static void *alloc(size_t size) {
	union hdr *tmp, **prev;
	size_t units;

	if (size == 0)
		return NULL;
	units = (size-1)/sizeof(union hdr) + 1;
	if (free_list == 0) {
		tmp = sbrk(MIN_ALLOC*sizeof(union hdr));
		if (tmp == (void *) -1) {
			dbg("ERROR: can't get more memory from the system\n");
			return NULL;
		}
		tmp->s.size = MIN_ALLOC - 1;
		tmp->s.next = NULL;
		free_list = tmp;
	}

	for (tmp = free_list, prev = 0; tmp; prev = &tmp, tmp = tmp->s.next) {
		if (tmp->s.size >= units) {
			if ((tmp->s.size - units) >= 2) /* need fragmentation */ {
				(tmp + tmp->s.size + 1)->s.next = tmp->s.next;
				(tmp + tmp->s.size + 1)->s.size = tmp->s.size - units - 1; /* -1 for header */
				tmp->s.next = (tmp + tmp->s.size + 1);
				tmp->s.size = units;
			}
			if (prev) {
				(*prev)->s.next = tmp->s.next;
			} else {
				free_list = tmp->s.next;
			}
			return tmp+1;
		}
		tmp = tmp->s.next;
	}

	return NULL;
}

static void dump_hdr(union hdr *p) {
	trace(">>> %s(p=%p) >>> p->next=%p, p->size=%u\n", __FUNCTION__, p, p->s.next, p->s.size);
}

int main(void) {
	int i;
	int *p = sbrk(0);
	int *pp;

	/* initialize */
	dbg_output_stream = stderr;

	mem_dump();
	printf("array of 15 bytes\n");
	pp = alloc(15);
	printf("array of 15 bytes are at %p\n", pp);
	dump_hdr(((union hdr *)pp) - 1);
	mem_dump();
	printf("array of 2 doubles\n");
	pp = alloc(2 * sizeof(double));
	printf("array of 2 doubles are at %p\n", pp);
	dump_hdr(((union hdr *)pp) - 1);
	mem_dump();
	printf("array of 7 floats\n");
	pp = alloc(7 * sizeof(float));
	printf("array of 7 floats are at %p\n", pp);
	dump_hdr(((union hdr *)pp) - 1);
	mem_dump();

	return 0;

	printf("sbrk(0) = %p\n", p);
	printf("*p = %08x\n", *p);
	printf("read 256 ints past break:\n");
	for (i = 0; i < 256; i++) {
		printf("i:%d\t", i);
		fflush(stdout);
		printf("[%p] 0x%08x\n", p, *p);
		p++;
	}

	return 0;
}
