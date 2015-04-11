#include "digraph.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

static link *last;

Digraph initDigraph(int V) {
    Digraph G = malloc(sizeof( *G));
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    last = malloc(V * sizeof(link));
    G->degrees = calloc(V ,sizeof(int));
    for (Vertex v = 0; v < V; v++)
        last[v] = G->adj[v] = NULL;
    return G;
}

void readDigraph(Digraph G) {
    for (Vertex v = 0; v < G->V; v++) {
        scanf("%d", &G->degrees[v]);
        for (int k = 0; k < G->degrees[v]; k++){
            Vertex w;
            scanf("%d", &w);
            if (v < w) {
                link new = malloc(sizeof(link));
                link antinew = malloc(sizeof(link));
                new->w = w;
                antinew->w = v;
                new->antiparallel = antinew;
                antinew->antiparallel = new;
                if (G->adj[v] == NULL) {
                    last[v] = new;
                    new->next = NULL;
                    G->adj[v] = new;
                }
                else {
                    last[v]->next = new;
                    new->next = NULL;
                    last[v] = new;
                }
                if (G->adj[w] == NULL) {
                    last[w] = antinew;
                    antinew->next = NULL;
                    G->adj[w] = antinew;
                }
                else {
                    last[w]->next = antinew;
                    antinew->next = NULL;
                    last[w] = antinew;
                }
            }
        }
    }
    free(last);
}

void printDigraph(Digraph G) {
    for (Vertex v = 0; v < G->V; v++)
        for (link a = G->adj[v]; a != NULL; a = a->next)
            printf("arco: %d - %d bloco: %d\n", v, a->w, a->block);
}

void freeDigraph(Digraph G) {
    free(G->degrees);
    for (Vertex i = 0; i < G->V; i++) {
        link a = G->adj[i];
        while (a != NULL) {
            link aux = a;
            printf("Liberando o %d %d \n", i, aux->w);
            a = a->next;
            free(aux);
        }
    }
    free(G->adj);
    free(G);
}


