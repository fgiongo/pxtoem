CC=cc
CFLAGS=-Wall -Wextra -std=c99 -O0 -ggdb
OBJ= main.o

make: main.o pxtoem.o Text.o
	$(CC) $(CFLAGS) -o pxtoem main.o pxtoem.o Text.o

main.o: main.c pxtoem.h Text.h
	$(CC) $(CFLAGS) -c -o main.o main.c

pxtoem.o: pxtoem.c pxtoem.h Text.h
	$(CC) $(CFLAGS) -c -o pxtoem.o pxtoem.c

Text.o: Text.c Text.h
	$(CC) $(CFLAGS) -c -o Text.o Text.c

.PHONY: clean

clean:
	rm -f *.o
