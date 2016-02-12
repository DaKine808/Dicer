CC=gcc
CFLAGS=-Wall -g

all:
	$(CC) $(CFLAGS) main.c helpers.c highLow.c syntax.c -o dicer
