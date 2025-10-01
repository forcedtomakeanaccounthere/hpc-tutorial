#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 100

typedef struct {
    int adj[MAX][MAX];
    int visited[MAX];
    int n;
} Graph;

void bfs(Graph* g, int start) {
    int queue[MAX], front = 0, rear = 0;
    g->visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int size = rear - front;

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int node = queue[front + i];
            printf("Thread %d visiting node %d (BFS)\n", omp_get_thread_num(), node);

            for (int j = 0; j < g->n; j++) {
                if (g->adj[node][j] && !g->visited[j]) {
                    #pragma omp critical
                    {
                        if (!g->visited[j]) {
                            g->visited[j] = 1;
                            queue[rear++] = j;
                            printf("Thread %d discovered node %d from node %d\n",
                                   omp_get_thread_num(), j, node);
                        }
                    }
                }
            }
        }
        front += size;
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

    printf("Parallel BFS starting from node 0:\n");
    bfs(&g, 0);
    printf("\n");
    return 0;
}
