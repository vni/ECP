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
	long double alignment;
	struct {
		union hdr *next;
		size_t size; /* in sizeof(union hdr) byte units */
	} s;
};

static union hdr *free_list;
static union hdr *used_list;

static void mem_dump(void) {
	union hdr *cursor;
	for (cursor = free_list; cursor; cursor = cursor->s.next) {
		trace("**********************\n");
		trace("hdr.next=%08x\n", cursor->s.next);
		trace("hdr.size=%u\n", cursor->s.size);
	}
}

static void *alloc(unsigned size) {
	if (size == 0)
		return NULL;
	trace("alloc(%u) bytes\n", size);
	size = (size-1)/sizeof(union hdr) + 1;
	union hdr *tmp;
	trace("alloc(%u) units\n", size);
	if (free_list == 0) {
		trace("initial allocation of memory\n");
		tmp = sbrk(MIN_ALLOC*sizeof(union hdr));
		if (tmp == (void *) -1) {
			dbg("ERROR: can't get more memory from the system\n");
			return NULL;
		}
		trace("old break is at %08x\n", tmp);
		trace("new break is at %08x\n", sbrk(0));
		tmp->s.size = MIN_ALLOC - 1;
		tmp->s.next = NULL;
		free_list = tmp;
	}

	return NULL;

#if 0
	for (tmp = free_list->next; tmp; tmp = tmp->next) {
		if (tmp.size >= size) {
			if ((tmp.size - size) > sizeof(union hdr)) { /* fragment big peace */
				size_t newsz = ((tmp.size/sizeof(union hdr)+1) - (size/sizeof(union hdr)+1)) * sizeof(union hdr);
				tmp.size = (size/sizeof(union hdr) + 1);
				tmp.next += tmp.size;
				tmp.next->size =
			}
		}
	}
#endif
}

int main(void) {
	int i;
	int *p = sbrk(0);
	int *pp;

	/* initialize */
	dbg_output_stream = stderr;

	printf("sizeof(long double)=%u\n", sizeof(long double));

	mem_dump();
	pp = alloc(15);
	printf("array of 15 ints are at %p\n", pp);
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
