#Makefile for blotto
#James Stanley 2010

CFLAGS=-Wall -O3 -g
OUT=blotto genteam
PREFIX?=/usr

all: $(OUT)
.PHONY: all

blotto: blotto.c wh_getline.c
	$(CC) $(CFLAGS) -o blotto blotto.c wh_getline.c

genteam: genteam.c
	$(CC) $(CFLAGS) -o genteam genteam.c

clean:
	-rm -f $(OUT)
.PHONY: clean

install:
	install -m 0755 blotto $(DESTDIR)$(PREFIX)/bin
	install -m 0755 genteam $(DESTDIR)$(PREFIX)/bin
.PHONY: install
