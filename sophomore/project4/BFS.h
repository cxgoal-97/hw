#include <iostream>
#include "Graphm.h"
#include <queue>

using namespace std;

void BFS(Graph* G, int start, queue<int>* Q){
    int v, w;
    Q->push(start);
    G->setMark(start, VISITED);
    while (Q->size() != 0){
        v = Q -> front();
        Q -> pop();

        for (w=G->first(v); w<G->n(); w = G->next(v, w))
            if (G -> getMark(w) == UNVISITED ) {
                G -> setMark(w, VISITED);
                Q -> push(w);
            }
    }
}

