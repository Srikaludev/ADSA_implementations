#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 7

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf("%d ", j + 1);
}

void printSolution(int dist[], int n, int parent[], int source) {
    printf("Shortest path to %d: %d ", n + 1, source + 1);
    printPath(parent, n);
    printf(": cost = %d\n", dist[n]);
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (i != src) {
            printSolution(dist, i, parent, src);
        }
    }
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0, 0},
        {0, 8, 0, 7, 0, 4, 0},
        {0, 0, 7, 0, 9, 14, 0},
        {0, 0, 0, 9, 0, 10, 0},
        {0, 0, 4, 14, 10, 0, 2},
        {0, 0, 0, 0, 0, 2, 0}
    };

    int source2 = 6;  // Source vertex for Dijkstra's algorithm
    dijkstra(graph, source2);

    return 0;
}