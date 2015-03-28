CC=gcc
CFLAGS=-Wall

all:
	$(CC) $(CFLAGS) main.c helpers.c highLow.c syntax.c -o dicer
