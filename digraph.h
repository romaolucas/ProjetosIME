#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED
#define Vertex int
#define Block int

typedef struct node *link;

struct node {
    Vertex w;
    Block block;
    link next;
    link antiparallel;
};

struct digraph {
    int V;
    int A;
    link *adj;
    int *degrees;
};

typedef struct digraph *Digraph;

Digraph initDigraph(int V);

void readDigraph(Digraph G);

void printDigraph(Digraph G);

void freeDigraph(Digraph G);

#endif
