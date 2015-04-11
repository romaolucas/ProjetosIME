#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"
#include "stack.h"

#define MaxV 10000
#define infty -1

static int tempo, d[MaxV], f[MaxV];
static Vertex parent[MaxV], low[MaxV];
int cutvertex;
int blocks;
Stack s;

void DFS(Digraph G) {
    tempo = cutvertex = 0;
    s = stackInit();
    blocks = 0;
    for (Vertex v = 0; v < G->V; v++) 
        d[v] = f[v] = -1;
    for (Vertex v = 0; v < G->V; v++) {
        if (d[v] == -1) {
            parent[v] = v;
            DFSVisit(G, v);
        }
    }
    while (!isEmpty(s)) {
        link a = pop(s);
        a->block = a->antiparallel->block = blocks;
    }
    freeStack(s);
}

void DFSVisit(Digraph G, Vertex u) {
    d[u] = tempo++;
    int children = 0;
    low[u] = d[u];
    for (link a = G->adj[u]; a != NULL; a = a->next) {
        if (d[a->w] == infty) {
            push(s, a);
            parent[a->w] = u;
            DFSVisit(G, a->w);
            children++;
            if (low[a->w] >= d[u]) {
                assignBlocks(s, a);
                printf("%d e vertice de corte\n", u);
                cutvertex++;
            }
            if (low[a->w] < low[u]) low[u] = low[a->w];
        }
        else if (f[a->w] == infty) {
            if (a->w != parent[u]) {
                push(s, a);
                if (d[a->w] < low[u]) low[u] = d[a->w];
            }
        }
    }
    f[u] = tempo++;
    if (parent[u] == u) {
        if (children >= 2) {
            printf("%d e vertice de corte\n", u);
            cutvertex++;
        }
    }
}

void assignBlocks(Stack s, link edge) {
    link u;
    do {
        u = pop(s);
        u->block = u->antiparallel->block = blocks;
    } while (u != edge);
    blocks++;
}
