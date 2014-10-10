all: vuln libsh.so

vuln: vuln.c
	gcc -g -Wall -o $@ $^

libsh.so: libsh.o
	gcc -shared -Wl,-soname,$@ -o $@ $<

libsh.o: libsh.c
	gcc -fPIC -c $<

clean:
	rm *.o libsh.so vuln

run:
	LD_PRELOAD=./libsh.so ./vuln
