#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED
#define Vertex int
#define Block int

typedef struct node *link;

struct node {
    Vertex w;
    Block block;
    link next;
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

void insertArc(Digraph G, Vertex v, Vertex w);

void freeDigraph(Digraph G);

#endif
