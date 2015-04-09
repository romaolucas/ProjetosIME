#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED
#include "digraph.h"

void DFS(Digraph G);

void DFSVisit(Digraph G, Vertex u);

extern int bridge, cutvertex;

#endif
