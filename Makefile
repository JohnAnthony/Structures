IDIR = include
SDIR = src
ALL_O = list.o
CFLAGS+= -std=c11 -Wall -pedantic -O2 -ggdb -I$(IDIR)
CC = cc

all: $(ALL_O)

%.o: $(SDIR)/%.c $(IDIR)/%.h
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	-rm -fv $(ALL_O)

.PHONY: clean
