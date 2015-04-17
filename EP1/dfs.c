#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"
#include "stack.h"

#define MaxV 10000
#define infty -1
#define TRUE 1
#define FALSE 0

static int tempo, d[MaxV];
static Vertex parent[MaxV], low[MaxV];
int cutvertex, blocks;
Stack s;

void DFS(Digraph G) {
    tempo = cutvertex = 0;
    s = stackInit();
    blocks = 0;
    for (Vertex v = 0; v < G->V; v++) 
        d[v] = -1;
    for (Vertex v = 0; v < G->V; v++) {
        if (d[v] == -1) {
            parent[v] = v;
            DFSVisit(G, v);
        }
        if (G->degrees[v] == 0)
            cutVertex = addCutVertex(v);
    }
    freeStack(s);
}

void DFSVisit(Digraph G, Vertex u) {
    d[u] = tempo++;
    int children = 0;
    low[u] = d[u];
    int iscutvertex = FALSE;
    for (link a = G->adj[u]; a != NULL; a = a->next) {
        if (d[a->w] == infty) {
            push(s, a);
            parent[a->w] = u;
            DFSVisit(G, a->w);
            children++;
            if (low[a->w] >= d[u]) {
                assignBlocks(s, a);
                if (parent[u] != u) {
                    iscutvertex = TRUE;
                }
            }
            low[u] = min(low[u], low[a->w]);
        }
        else if ((parent[u] != a->w) && (d[a->w] < d[u])) {
                push(s, a);
                low[u] = min(low[u], d[a->w]);
        }
    }
    if (parent[u] == u) {
        if (children >= 2) {
            iscutvertex = 1;
        }
    }
    if (iscutvertex) {
        cutvertex++;
        cutVertex = addCutVertex(u);
    }
}

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

void assignBlocks(Stack s, link edge) {
    link u;
    do {
        u = pop(s);
        u->block = u->antiparallel->block = blocks;
    } while (u != edge);
    blocks++;
}

void buildNewDigraph(Digraph G) {
    for (cutList p = cutVertex; p != NULL; p = p->next)
        p->block = blocks++;
    for (cutList p = cutVertex; p != NULL; p = p->next)
        printf("%d %d\n", p->v, p->block);
    printf("%d \n", blocks);
    Digraph newG = initDigraph(blocks);
    link *last = malloc(blocks * sizeof(link));
    int *visited = malloc(blocks * sizeof(int));
    for (Vertex v = 0; v < blocks; v++) {
        last[v] = NULL;
        visited[v] = -1;
    }
    for (cutList p = cutVertex; p != NULL; p = p->next) {
        for (link a = G->adj[p->v]; a != NULL; a = a->next) {
            if (visited[a->block] != p->v) {
                link new = malloc(sizeof(link));
                link antinew = malloc(sizeof(link));
                new->w = a->block;
                new->antiparallel = antinew;
                antinew->antiparallel = new;
                antinew->w = p->block;
                if (newG->adj[a->block] == NULL) {
                    last[a->block] = antinew;
                    antinew->next = NULL;
                    newG->adj[a->block] = antinew;
                }
                else {
                    last[a->block]->next = antinew;
                    antinew->next = NULL;
                    last[a->block] = antinew;
                }
                if (newG->adj[p->block] == NULL) {
                    last[p->block] = new;
                    new->next = NULL;
                    newG->adj[p->block] = new;
                }
                else {
                    last[p->block]->next = new;
                    new->next = NULL;
                    last[p->block] = new;
                }
            }
            visited[a->block] = p->v;
        }
    }
    free(last);
    free(visited);
    freeCutList();
    for (Vertex v = 0; v < newG->V; v++)
        for (link a = newG->adj[v]; a != NULL; a = a->next)
            newG->degrees[v]++;
    for (Vertex v = 0; v < newG->V; v++) {
        printf("%d ", newG->degrees[v]);
        for (link a = newG->adj[v]; a != NULL; a = a->next)
            printf("%d ", a->w);
        printf("\n");
    }
    freeDigraph(newG);
}
