CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99 -g

teste: main.c digraph.o dfs.o
	$(CC) $^ -o $@ $(CFLAGS) 

dfs.o: dfs.c digraph.o dfs.h digraph.h
	$(CC) $(CFLAGS) -c dfs.c

digraph.o: digraph.c digraph.h
	$(CC) $(CFLAGS) -c digraph.c 

clean:
	rm -f *.o



