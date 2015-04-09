#include "digraph.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

Digraph initDigraph(int V) {
    Digraph G = malloc(sizeof( *G));
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    G->degrees = calloc(V ,sizeof(int));
    for (Vertex v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void readDigraph(Digraph G) {
    for (Vertex v = 0; v < G->V; v++) {
        scanf("%d", &G->degrees[v]);
        for (int k = 0; k < G->degrees[v]; k++){
            Vertex w;
            scanf("%d", &w);
            insertArc(G, v, w);
        }
    }
}

void insertArc(Digraph G, Vertex v, Vertex w) {
    link new = malloc(sizeof( struct node));
    new->w = w;
    new->block = 0;
    new->next = G->adj[v];
    G->adj[v] = new;
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


