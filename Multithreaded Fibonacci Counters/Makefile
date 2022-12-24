.PHONY: clean

CC = gcc

CFLAGS = -g

CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic

objLin = obj/linux/

objWin = obj/windows/

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)

all: $(objLin)/ posixThreads

else

all: $(objWin)/ winThreads

endif

# Windows threads

winThreads: winThreads.o FibWindows.o

	$(CC) -o winThreads $(CFLAGS) $(CPPFLAGS) $(objWin)winThreads.o $(objWin)FibWindows.o


winThreads.o: winThreads.c threads.h

	$(CC) -o $(objWin)winThreads.o -c $(CFLAGS) $(CPPFLAGS) winThreads.c


FibWindows.o: Fib.c threads.h

	$(CC) -o $(objWin)FibWindows.o -c $(CFLAGS) $(CPPFLAGS) Fib.c

# Posix threads

posixThreads: posixThreads.o FibLinux.o

	$(CC) -o posixThreads $(CFLAGS) $(CPPFLAGS) $(objLin)posixThreads.o $(objLin)FibLinux.o


posixThreads.o: posixThreads.c threads.h

	$(CC) -o $(objLin)posixThreads.o -c $(CFLAGS) $(CPPFLAGS) posixThreads.c -lpthread


FibLinux.o: Fib.c threads.h

	$(CC) -o $(objLin)FibLinux.o -c $(CFLAGS) $(CPPFLAGS) Fib.c


# create directories
$(objLin)/:

	mkdir -p $(objLin)

$(objWin)/:

	mkdir -p $(objWin)

clean:

	rm -rf *.o $(objWin)*.o $(objLin)*.o winThreads posixThreads obj/
