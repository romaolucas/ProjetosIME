#include "digraph.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

cutList cutVertex = NULL;

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
    link *last = malloc(G->V* sizeof(link));
    for (Vertex v = 0; v < G->V; v++)
        last[v] = NULL;
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
    printf("%d\n", G->V);
    for (Vertex v = 0; v < G->V; v++) {
        printf("%d ", G->degrees[v]);
        for (link a = G->adj[v]; a != NULL; a = a->next)
            printf("%d ", a->block);
        printf("\n");
    }   
}

void freeDigraph(Digraph G) {
    free(G->degrees);
    for (Vertex i = 0; i < G->V; i++) {
        link a = G->adj[i];
        while (a != NULL) {
            link aux = a;
            a = a->next;
            free(aux);
        }
    }
    free(G->adj);
    free(G);
}

cutList addCutVertex(Vertex u) {
    cutList new = malloc(sizeof(cutList));
    new->next = cutVertex;
    new->v = u;
    cutVertex = new;
    return cutVertex;
}

void freeCutList() {
    cutList p = cutVertex;
    while (p != NULL) {
        cutList q = p;
        p = p->next;
        free(q);
    }
}
