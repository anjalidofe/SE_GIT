#define MAX 10
 
//structure of graph
typedef struct graph{
    int A[MAX][MAX];
    int n;
}graph;

//structure of edge of graph having source, destination and weight
typedef struct edge{
    int src, dest;
    int weight;
}edge;

//functions
void dfs(graph *G, int x);
edge *prim(graph G, int s);
int* djisktra(graph G, int s);
edge* kruskals(graph G);

