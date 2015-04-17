#include<stdio.h>
#include<stdlib.h>
#include "dfs.h"
#include "digraph.h"

int main() {
    int V;
    scanf("%d", &V);
    Digraph G = initDigraph(V);
    readDigraph(G);
    DFS(G);
    printDigraph(G);
    printf("%d\n", cutvertex);
    buildNewDigraph(G);
    freeDigraph(G);
    return 0;
}
