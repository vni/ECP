foo: main.o libfoo.a
	gcc main.o -lfoo -L. -o $@

main.o: main.c libfoo.h
	gcc -c $<

libfoo.a: libfoo.o
	ar rcs $@ $^

libfoo.o: libfoo.c libfoo.h
	gcc -c $<

clean:
	rm *.o *.a foo
