#include "iostream"
#include "Graphm.h"

using std::cout;

void DFS(Graph* G, int v){
    PreVisit(G, v);
    G->setMark(v, VISITED);
    for (int w = G->first(v); w<G->n(); w = G->next(v,w)){
        if (G->getMark(w) == UNVISITED)
            DFS(G, w);
    PostVisit(G,v);
}
