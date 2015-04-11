CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99 -g

blocks: main.c digraph.o dfs.o stack.o
	$(CC) $^ -o $@ $(CFLAGS) 

dfs.o: dfs.c dfs.h stack.h digraph.h
	$(CC) $(CFLAGS) -c dfs.c

stack.o: stack.c stack.h digraph.h
	$(CC) $(CFLAGS) -c stack.c

digraph.o: digraph.c digraph.h
	$(CC) $(CFLAGS) -c digraph.c 

clean:
	rm -f *.o



