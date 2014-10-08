foo: main.o libfoo.so
	@#gcc -o $@ main.o -L. -lfoo
	@#gcc -o $@ main.o -Wl,-rpath=. -L. -R. -lfoo
	@#ld -o $@ main.o -L. -R. -lfoo -lc
	ld -o $@ main.o -L. -R. -dynamic-linker /lib/ld-linux.so.2 -lfoo /usr/lib/crt1.o /usr/lib/crti.o -lc /usr/lib/crtn.o

main.o: main.c libfoo.h
	gcc -c $<

libfoo.so: libfoo.o
	@#gcc -shared -Wl,-soname,libfoo.so -o $@ $^
	ld -shared -soname=$@ -o $@ $^

libfoo.o: libfoo.c libfoo.h
	gcc -fPIC -c $<

run:
	LD_LIBRARY_PATH=. ./a.out how are your business?

clean:
	rm *.o *.so foo
