.PHONY: clean

CC = gcc

CFLAGS = -g

CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic

all: testlist-Linuxx86_64

testlist-Linuxx86_64: mytestlist.o liblistnode.a

	$(CC) -L./ -o testlist-Linuxx86_64 $(CFLAGS) $(CPPFLAGS) mytestlist.o -llistnode

liblistnode.a: list_adders.o list_movers.o list_removers.o

	ar -r -s -c liblistnode.a list_adders.o list_movers.o list_removers.o

list_adders.o: list_adders.c list.h

	$(CC) -o list_adders.o -c $(CFLAGS) $(CPPFLAGS) list_adders.c

list_movers.o: list_movers.c list.h

	$(CC) -o list_movers.o -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_removers.o: list_removers.c list.h

	$(CC) -o list_removers.o -c $(CFLAGS) $(CPPFLAGS) list_removers.c

mytestlist.o: mytestlist.c list.h

	$(CC) -o mytestlist.o -c $(CFLAGS) $(CPPFLAGS) mytestlist.c

clean:

	rm *.o *.a testlist-Linuxx86_64
