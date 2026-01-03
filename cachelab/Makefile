CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11 -O0 -ggdb -no-pie
LIBS:=-lm

OBJS = cachesim.o cache.o

all: cachesim

cachesim: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

cachesim.o: cachesim.c cache.h
	$(CC) $(CFLAGS) -c $< -o $@

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f cachesim
	

