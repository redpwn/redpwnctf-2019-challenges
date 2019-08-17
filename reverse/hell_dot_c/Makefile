.POSIX:

CFLAGS = -g -std=c99 -pedantic -Wfatal-errors

.PHONY: all

all: hell encrypt encrypted.inc

hell: hell.c encrypted.inc
	$(CC) $(CFLAGS) hell.c -o hell

encrypt: encrypt.c

encrypted.inc: encrypt flag.txt
	./encrypt < flag.txt > encrypted.inc
