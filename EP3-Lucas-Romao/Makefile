CC     = gcc
CFLAGS = -g -Wall -O2 -ansi -pedantic -Wno-unused-result
#------------------------------------------------

# chama o linker
pitao:  main.o eval.o lexer.o util.o stack.o
	$(CC) main.o eval.o lexer.o util.o stack.o -o pitao -lm

main.o: main.c eval.h lexer.h util.h classes.h   
	$(CC) $(CFLAGS) -c main.c 

eval.o: eval.c eval.h util.h classes.h stack.h
	$(CC) $(CFLAGS) -c eval.c 

lexer.o: lexer.c lexer.h util.h classes.h
	$(CC) $(CFLAGS) -c lexer.c 

util.o: util.c util.h classes.h 
	$(CC) $(CFLAGS) -c util.c 

stack.o: stack.c stack.h  util.h
	$(CC) $(CFLAGS) -c stack.c
