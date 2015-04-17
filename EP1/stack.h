#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "digraph.h"

typedef struct Node *node;

struct Node {
    link edge;
    node next;
};

struct stack {
   node top; 
};

typedef struct stack *Stack;


Stack stackInit();

void push(Stack s, link a);

link pop(Stack s);

int isEmpty(Stack s);

void freeStack(Stack s);

#endif
