#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"

#define MaxV 10000
#define infty -1

static int tempo, d[MaxV], f[MaxV];
static Vertex parent[MaxV], low[MaxV];
int bridge, cutvertex;

void DFS(Digraph G) {
    tempo = bridge = cutvertex = 0;
    for (Vertex v = 0; v < G->V; v++) 
        d[v] = f[v] = -1;
    for (Vertex v = 0; v < G->V; v++) {
        if (d[v] == -1) {
            parent[v] = v;
            DFSVisit(G, v);
        }
    }
    for (Vertex v = 0; v < G->V; v++) printf("pai %d\n", parent[v]);
}

void DFSVisit(Digraph G, Vertex u) {
    d[u] = tempo++;
    int children = 0;
    low[u] = d[u];
    int maxlow = infty;
    for (link a = G->adj[u]; a != NULL; a = a->next) {
        if (d[a->w] == -1) {
            parent[a->w] = u;
            DFSVisit(G, a->w);
            children++;
            if (low[a->w] < low[u]) low[u] = low[a->w];
            if (low[a->w] == d[a->w]) {
                printf("%d - %d e ponte\n", u, a->w);
                bridge++;
            }
            if (low[a->w] > maxlow) maxlow = low[a->w];
        }
        else if (f[a->w] == infty) {
            if (a->w != parent[u]) {
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
    else
        if (maxlow >= d[u]) {
            printf("%d e vertice de corte\n", u);
            cutvertex++;
        }
}
