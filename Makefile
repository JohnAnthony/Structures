IDIR = include
SDIR = src
ALL_O = list.o
CFLAGS+= -std=c11 -Wall -pedantic -O2 -ggdb -I$(IDIR)
CC = cc

all: test $(ALL_O)

test: test.c $(ALL_O)
	$(CC) -o $@ $(CFLAGS) $< $(ALL_O)

%.o: $(SDIR)/%.c $(IDIR)/%.h
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	-rm -fv test $(ALL_O)

.PHONY: clean
