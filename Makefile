CC=cc
CFLAGS=-Wall -Wextra -std=c99
OBJ= main.o

make: main.o
	$(CC) -o pxtoem main.o


main.o: main.c
	$(CC) -c -o main.o main.c

.PHONY: clean

clean:
	rm -f main.o
