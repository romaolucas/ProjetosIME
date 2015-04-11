#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED
#include "digraph.h"
#include "stack.h"

void DFS(Digraph G);

void DFSVisit(Digraph G, Vertex u);

void assignBlocks(Stack s, link edge);

extern int cutvertex;

#endif
