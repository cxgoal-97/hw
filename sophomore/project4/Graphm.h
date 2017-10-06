#include "Graph.h"

#define VISITED 1
#define UNVISITED 0

class Graphm: public    Graph{
    private:
        int numVertex, numEdge;
        int **matrix;
        int *mark;
    public:
        Graphm(int numVert) {Init(numVert)}

        ~Graphm(){
            delete [] mark;
            for (int i=0;i<numVertex;i++)
                delete [] matrix[i];
            delete [] matrix;
        }

        void Init(int n ){
            int i;
            numVertex = n;
            numEdge =0;
            mark = new int[n];
            for (i=0; i<numVertex; i++)
                matrix[i] = new int [numVertex];
            for (i=0; i<numVertex; i++)
                for (int j=0; j<numVertex; j++)
                    matrix[i][j] = 0;
        }

        int n() {   return numVertex;}
        int e() {   return numEdge;}

        int frist(int v){
            for (int i=0; i<numVertex; i++)
                if (matrix[v][i] != 0) return i;
            return numVertex;
        }

        int next(int v, int w){
            for(int i = w+1 ; i < numVertex ; i++ )
                if (matrix[v][i] == 1)
                    return i;
            return numVertex;
        }

        void setEdge(int v1, int v2 , int wt){
            if ( wt < 0)    cout<<"Illegal weight Value";
            if ( matrix[v1][v2] == 0)   numEdge++;
            matrix[v1][v2] = wt;
        }

        void delEdge(int v1, int v2){
            if (matrix[v1][v2] != 0) numEdge--;
            matrix[v1][v2] = 0;
        }
        bool isEdge(int i, int j){
            return matrix[i][j] != 0;
        }

        int weight(int v1, int v2) {   return matrix[v1][v2];  }
        int getMark(int v)  {   return mark[v];    }
        void setMark(int v, int val)    {   mark[v] = val;  }
};
