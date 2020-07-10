CC=gcc
CFLAGS=-I.

linecounter: line_counter.c
	$(CC) -Wall -o linecounter line_counter.c
