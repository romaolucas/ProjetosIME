#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED
#include "digraph.h"
#include "stack.h"

void DFS(Digraph G);

void DFSVisit(Digraph G, Vertex u);

int min(int a, int b);

void assignBlocks(Stack s, link edge);

void buildNewDigraph();

extern int cutvertex, blocks;

#endif
