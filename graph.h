#define MAX 10

typedef struct graph{
    int A[MAX][MAX];
    int n;
}graph;

typedef struct edge{
    int src, dest;
    int weight;
}edge;

void dfs(graph *G, int x);
edge *prim(graph G, int s);
int* djisktra(graph G, int s);
edge* kruskals(graph G);

