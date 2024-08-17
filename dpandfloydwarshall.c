#include <stdio.h>

#define INF 99999
#define V 4

// Part a: DP for Coin Change
int min(int a, int b) {
    return (a < b) ? a : b;
}

int coinChange(int coins[], int m, int amt) {
    int cut[amt + 1];
    cut[0] = 0;

    for (int i = 1; i <= amt; i++)
        cut[i] = INF;

    for (int i = 1; i <= amt; i++) {
        for (int j = 0; j < m; j++) {
            if (coins[j] <= i) {
                int mini = cut[i - coins[j]];
                if (mini != INF && mini + 1 < cut[i]) {
                    cut[i] = mini + 1;
                }
            }
        }
    }

    if (cut[amt] == INF) {
    return -1;
} else {
    return cut[amt];
}

}

// Part b: Floyd-Warshall Algorithm 


void floydWarshall(int graph[V][V]) {
    int key[V][V];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            key[i][j] = graph[i][j];

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (key[i][k] + key[k][j] < key[i][j])
                    key[i][j] = key[i][k] + key[k][j];
            }
        }
    }

    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (key[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", key[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Part a: Coin Change Example
   int coins[] = {2, 4, 6, 8};
    int amt_a = 18;
    int result_a = coinChange(coins, sizeof(coins) / sizeof(coins[0]), amt_a);
    printf("Part a: Coin Change Result: %d\n", result_a);

    // Part b: Floyd-Warshall Example
    int graph[V][V] = {{0, 2, INF, 5},
                       {INF, 0, 7, INF},
                       {INF, INF, 0, 1},
                       {INF, INF, INF, 0}};

    printf("\nPart b: Floyd-Warshall Shortest keyances:\n");
    floydWarshall(graph);

    return 0;
}