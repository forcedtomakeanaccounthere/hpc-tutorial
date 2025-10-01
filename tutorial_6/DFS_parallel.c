#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 100

typedef struct {
    int adj[MAX][MAX];
    int visited[MAX];
    int n;
} Graph;

void dfs(Graph* g, int node) {
    int alreadyVisited = 0;

    // Mark node visited safely
    #pragma omp critical
    {
        if (g->visited[node]) {
            alreadyVisited = 1;
        } else {
            g->visited[node] = 1;
            printf("Thread %d visiting node %d (DFS)\n", omp_get_thread_num(), node);
        }
    }

    if (alreadyVisited) return; // return *outside* critical section

    // Explore neighbors in parallel
    #pragma omp parallel for
    for (int i = 0; i < g->n; i++) {
        if (g->adj[node][i] && !g->visited[i]) {
            dfs(g, i);
        }
    }
}

int main() {
    Graph g = {0};
    g.n = 6;

    // Example adjacency matrix (undirected)
    g.adj[0][1] = g.adj[1][0] = 1;
    g.adj[0][2] = g.adj[2][0] = 1;
    g.adj[1][3] = g.adj[3][1] = 1;
    g.adj[2][4] = g.adj[4][2] = 1;
    g.adj[3][5] = g.adj[5][3] = 1;

    printf("Parallel DFS starting from node 0:\n");
    dfs(&g, 0);
    printf("\n");
    return 0;
}
