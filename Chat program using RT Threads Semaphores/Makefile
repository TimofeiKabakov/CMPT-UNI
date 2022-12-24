.PHONY: clean

CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic

pathToRt =
objLin = obj/linux/
binLin = mybin/linux/
libLin = lib/linux/

ARCH = $(shell uname -m)

all: $(objLin)/ $(libLin)/ reader-writer-test s-chat_$(ARCH)

s-chat_$(ARCH): s-chat_$(ARCH).o
	$(CC) -o s-chat_$(ARCH) $(CFLAGS) $(CPPFLAGS) $(objLin)s-chat_$(ARCH).o \
	-L/$(pathToRt) -L./$(libLin) \
	-lRtt -ltirpc -lRttUtils -llistnode

s-chat_$(ARCH).o: s-chat.c
	$(CC) -o $(objLin)s-chat_$(ARCH).o -c $(CFLAGS) $(CPPFLAGS) s-chat.c \
	-I/$(pathToRt)/include -I.

liblistnode.a: list_adders.o list_movers.o list_removers.o
	ar -r -s -c $(libLin)liblistnode.a $(objLin)list_adders.o \
	$(objLin)list_movers.o $(objLin)list_removers.o

list_adders.o: list_adders.c list.h
	$(CC) -o $(objLin)list_adders.o -I. -c $(CFLAGS) $(CPPFLAGS) list_adders.c

list_movers.o: list_movers.c list.h
	$(CC) -o $(objLin)list_movers.o -I. -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_removers.o: list_removers.c list.h
	$(CC) -o $(objLin)list_removers.o -I. -c $(CFLAGS) $(CPPFLAGS) \
	list_removers.c

$(objLin)/:
	mkdir -p $(objLin)

$(libLin)/:
	mkdir -p $(libLin)

clean:
	rm -rf *.o $(binLin)*.o $(objLin)*.o $(libLin)*.a obj/ mybin/ lib/ s-chat_$(ARCH)
