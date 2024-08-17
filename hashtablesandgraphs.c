#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define TABLE_SIZE 100
#define MAX_KEY_LENGTH 100
#define LOAD_FACTOR_THRESHOLD 0.7

typedef struct KeyValue {
    char key[MAX_KEY_LENGTH];
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct ListN {
    int destination;
    struct ListN* next;
} ListN;

typedef struct HashTable {
    KeyValue *table[TABLE_SIZE];
    int size;
} HashTable;

typedef struct Graph {
    int nVert;
    ListN* adjLists[MAX_VERTICES];
} Graph;

KeyValue *newKeyValue(char *key, int value) {
    KeyValue *kv = (KeyValue *)malloc(sizeof(KeyValue));
    strncpy(kv->key, key, MAX_KEY_LENGTH);
    kv->value = value;
    kv->next = NULL;
    return kv;
}

HashTable *createHashTable() {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    ht->size = 0;
    return ht;
}

int hash(char *key) {
    int hash = 0;
    while (*key) {
        hash = (hash + *key) % TABLE_SIZE;
        key++;
    }
    return hash;
}

void put(HashTable *ht, char *key, int value) {
    int index = hash(key);
    KeyValue *newPair = newKeyValue(key, value);

    
    KeyValue *present = ht->table[index];
    while (present != NULL) {
        if (strcmp(present->key, key) == 0) {
            present->value = value;
            free(newPair);
            return;
        }
        present = present->next;
    }
    newPair->next = ht->table[index];
    ht->table[index] = newPair;
    ht->size++;

   
    if ((float)ht->size / TABLE_SIZE > LOAD_FACTOR_THRESHOLD) {
        
        printf("Resize the hash table...\n");
    }
}

int get(HashTable *ht, char *key) {
    int index = hash(key);
    KeyValue *present = ht->table[index];

    while (present != NULL) {
        if (strcmp(present->key, key) == 0) {
            return present->value;
        }
        present = present->next;
    }

    return -1;
}


void removeKey(HashTable *ht, char *key) {
    int index = hash(key);
    KeyValue *present = ht->table[index];
    KeyValue *prev = NULL;

    while (present != NULL) {
        if (strcmp(present->key, key) == 0) {
            if (prev == NULL) {
                ht->table[index] = present->next;
            } else {
                prev->next = present->next;
            }
            free(present);
            ht->size--;
            return;
        }
        prev = present;
        present = present->next;
    }
}

ListN* newListN(int destination) {
    ListN* newNode = (ListN*)malloc(sizeof(ListN));
    newNode->destination = destination;
    newNode->next = NULL;
    return newNode;
}


Graph* createGraph(int nVert) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->nVert = nVert;
    for (int i = 0; i < nVert; ++i) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int source, int destination) {
    ListN* newNode = newListN(destination);
    newNode->next = graph->adjLists[source];
    graph->adjLists[source] = newNode;

    newNode = newListN(source);
    newNode->next = graph->adjLists[destination];
    graph->adjLists[destination] = newNode;
}

void removeEdge(Graph* graph, int source, int destination) {
    ListN* present = graph->adjLists[source];
    ListN* prev = NULL;

    while (present != NULL && present->destination != destination) {
        prev = present;
        present = present->next;
    }

    if (present == NULL) {
       
        return;
    }

    if (prev == NULL) {
        
        graph->adjLists[source] = present->next;
    } else {
        prev->next = present->next;
    }

    free(present);

    present = graph->adjLists[destination];
    prev = NULL;

    while (present != NULL && present->destination != source) {
        prev = present;
        present = present->next;
    }

    if (present == NULL) {
        
        return;
    }

    if (prev == NULL) {
        graph->adjLists[destination] = present->next;
    } else {
        prev->next = present->next;
    }

    free(present);
}
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->nVert; ++i) {
        ListN* present = graph->adjLists[i];
        printf("Adjacency list for vertex %d: ", i);
        while (present != NULL) {
            printf("%d ", present->destination);
            present = present->next;
        }
        printf("\n");
    }
}



int hasPathDFS(Graph* graph, int source, int destination, int visited[]) {
    if (source == destination) {
        return 1; // Path found
    }

    visited[source] = 1;

    ListN* present = graph->adjLists[source];
    while (present != NULL) {
        int adjacentVertex = present->destination;
        if (!visited[adjacentVertex]) {
            if (hasPathDFS(graph, adjacentVertex, destination, visited)) {
                return 1; // Path found
            }
        }
        present = present->next;
    }

    return 0; // Path not found
}

int hasPath(Graph* graph, int source, int destination) {
    if (source < 0 || source >= graph->nVert || destination < 0 || destination >= graph->nVert) {
        return 0; // Invalid source or destination
    }

    int* visited = (int*)calloc(graph->nVert, sizeof(int));

    int result = hasPathDFS(graph, source, destination, visited);

    free(visited);

    return result;
}







// Main function to test the hash table
int main() {
    HashTable *ht = createHashTable();

    put(ht, "John", 25);
    put(ht, "Alice", 30);
    put(ht, "Bob", 22);

    printf("John's age: %d\n", get(ht, "John"));  // Output: John's age: 25

    removeKey(ht, "Alice");
    printf("Alice's age: %d\n", get(ht, "Alice"));  // Output: Alice's age: -1





    Graph* graph = createGraph(5);

    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Print the graph
    printGraph(graph);


    int source = 0;
    int destination = 4;
    if (hasPath(graph, source, destination)) {
        printf("There is a path between vertex %d and vertex %d.\n", source, destination);
    } else {
        printf("There is no path between vertex %d and vertex %d.\n", source, destination);
    }

    // Remove an edge
    removeEdge(graph, 2, 3);

    // Print the updated graph
    printf("Updated graph after removing an edge:\n");
    printGraph(graph);

    // Clean up
    free(graph);

    return 0;
}