#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

Stack stackInit() {
    Stack s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

int isEmpty(Stack s) {
    return s->top == NULL; 
}

void push(Stack s, link a) {
    if (isEmpty(s)) {
        s->top = malloc(sizeof(node));
        s->top->next = NULL;
        s->top->edge = a;
    }
    else {
        node p = malloc(sizeof(node));
        p->edge = a;
        p->next = s->top;
        s->top = p;
    }
}

link pop(Stack s) {
    node a = s->top;
    link value = a->edge;
    s->top = a->next;
    free(a);
    return value;
}

void freeStack(Stack s) {
    while (!isEmpty(s)) {
        node q = s->top;
        s->top = q->next; 
        free(q);
    }
    free(s);
}


