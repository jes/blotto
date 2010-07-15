#Makefile for blotto
#James Stanley 2010

CFLAGS=-Wall -O3
OUT=blotto genteam

all: $(OUT)
.PHONY: all

clean:
	-rm -f $(OUT)
.PHONY: clean
