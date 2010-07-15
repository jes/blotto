#Makefile for blotto
#James Stanley 2010

CFLAGS=-Wall -O3
OUT=blotto genteam
PREFIX?=/usr

all: $(OUT)
.PHONY: all

clean:
	-rm -f $(OUT)
.PHONY: clean

install:
	install -m 0755 blotto $(DESTDIR)$(PREFIX)/bin
	install -m 0755 genteam $(DESTDIR)$(PREFIX)/bin
.PHONY: install
