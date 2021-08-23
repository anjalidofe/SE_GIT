
#include "graph.h"
#include <stdio.h>
#include "stack.h"
#include "Queue.h"
#include "limits.h"

void initGraph(graph *G, char *filename){
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return ;
    int n ;
    fscanf(fp, "%d", &n);
    G->n = n;
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0 ;j < n; j++)
            fscanf(fp, "%d", &G->A[i][j]);
    return ;    
}

void printGraph(graph G){
    for (int i = 0; i < G.n; i++){
        for (int j = 0; j < G.n; j++)
            printf("%d ", G.A[i][j]);
        printf("\n");
    }
}

void dfs(graph *g, int x){
    int v, flag = 0;
    int* visited = (int*)calloc(g->n, sizeof(int));
    
    stack s;
    inits(&s, 20);
    push(&s, x);
    printf("\n%d - ", x);
    visited[x] = 1;
    while(!isEmptys(s)) {
        v = peek(s);
        for(int j = 0; j < g->n; j++){
            flag = 0;
            if(g->A[v][j] == 1 && !(visited[j])){
                push(&s, j);
                printf("%d - ", j);
                visited[j] = 1;
                flag = 1;
                break;
            }
        }
        if(!flag)
            pop(&s);
    }
    return;
}

void bfs(graph *g, int x){
    int *visited = (int*)calloc(g->n, sizeof(int));
    queue q;
    initq(&q, 20);
    enqueue(&q, x);
    printf("\n%d - ", x);
    visited[x] = 1;
    int v;
    while(!isEmptyq(q)){
        v = dequeue(&q);
        for(int j = 0; j < g->n; j++){
            //flag = 0;
            if(g->A[v][j] == 1 && !visited[j]){
                enqueue(&q, j);
                printf("%d - ", j);
                visited[j] = 1;
                //flag = 1;
            }
        }
    }
    return;
}

edge *prims(graph G, int x){
    int d = G.n;
    edge *prims = (edge*)malloc(sizeof(edge) * (d - 1));
    int *visited = (int*)calloc(d, sizeof(int));
    visited[x] = 1;
    int k = 0;

    edge minedge;
    int minwt = INT_MAX;

    while (k < d - 1){
        for(int u = 0; u < d - 1; u++){
            minwt = INT_MAX;
            for (int v = 0; v < d - 1 ; v++){                
                if (visited[u] && !visited[v]){
                    if (G.A[u][v] && G.A[u][v] < minwt){
                        minwt = G.A[u][v];
                        minedge.src = u;
                        minedge.dest = v;
                        minedge.weight = minwt;                       
                    }
                }
            }
        }
        prims[k] = minedge;
        visited[minedge.dest] = 1;
        k++; 
    }
    return prims;
}
 
 //visited array
 //cost array
 //select min cost vertex v
 //relaxation of all the remainig unvisited wrt vertex v
 //repeat n-1 times
int* djikstras(graph G, int s){
    int d = G.n;
    int *visited = (int*)calloc(d, sizeof(int));
    visited[s] = 1;

    int *cost = (int*)malloc(sizeof(int) * d);

    for (int i = 0; i < d; i++){
        if (G.A[s][i])
            cost[i] = G.A[s][i];
        else
            cost[i] = INT_MAX;
    }
    
    cost[s] = 0;

    int minw , minv;

    for (int k = 0; k < d- 1 ; k++){
        minw = INT_MAX;
        
        for (int j = 0 ;j < d; j++){
            if (!visited[j] && cost[j] < minw){
                minw = cost[j];
                minv = j;
            }
        }

        visited[minv] = 1;

        for (int u = 0; u < d; u++)
            if (!visited[u] && G.A[minv][u] && cost[u]  > cost[minv] + G.A[minv][u])
                cost[u] = cost[minv] + G.A[minv][u];

    }
    return cost;
}





edge* kruskals(graph G){
    int d = G.n;
    edge *kruskals = (edge*)malloc(sizeof(edge) * (d-1));
    //make set
    int *set = (int*)malloc(sizeof(int)*d);

    for (int i = 0 ;i < d; i++)
        set[i] = -1;

    //array for non decreasing order of edges
    edge* edges_ND = (edge*)malloc(sizeof(edge) * (d*d));
    //copy to array
    int k = 0;
    for (int i = 0; i < G.n; i++){
        for (int j = i ; j < G.n; j++){
            if (G.A[i][j]){
                edges_ND[k].src = i;
                edges_ND[k].dest = j;
                edges_ND[k].weight = G.A[i][j];
                k++;
            }
        }
    }
    //sort the array
    bubbleSort(edges_ND, k);

    int count = 0, u, v, m, n, wU,wV, z = 0;

    while (z < d - 1){
        u = edges_ND[count].src;
        v = edges_ND[count].dest;
        m = u;
        n = v;

        //parent of u
        while (set[m] >= 0){
            m = set[m];
        }
        //parent of v
        while (set[n] >= 0){
            n = set[n];
        }

        if ( m != n) {
            //union
            wU = -1 * set[m];
            wV = -1 * set[n];
            
            if (wU == wV || wU > wV){
                set[n] = m;
                set[m] -= wV;
            }
            else{
                set[m] = n;
                set[n] -= wU;
            }
            kruskals[z++] = edges_ND[count];
            
        }
        //otherwise discard as parents are same so cycle detected        
        
        count ++;
    }  
    
    return kruskals;   
    
}

void print (int *arr, int size){
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(edge *xp, edge *yp){
    edge temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
// A function to implement bubble sort
void bubbleSort(edge* arr, int n){
    int i, j;
    for (i = 0; i < n-1; i++)      
        for (j = 0; j < n-i-1; j++) 
            if (arr[j].weight > arr[j+1].weight)
                swap(&arr[j], &arr[j+1]);
    for (int z = 0; z < n; z++){
        printf("%d %d %d\n", arr[z].src, arr[z].dest, arr[z].weight);
    }
    printf("\n");
}



