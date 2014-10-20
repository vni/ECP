ALL=maxmem dumbcopy smartcopy
all: $(ALL)

maxmem: maxmem.c
	gcc -Wall -o $@ $<

dumbcopy: dumbcopy.c
	gcc -Wall -o $@ $<

smartcopy: smartcopy.c
	gcc -Wall -o $@ $<

clean:
	@rm -fv $(ALL)
