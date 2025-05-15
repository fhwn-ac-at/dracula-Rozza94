#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int from;
    int to;
    int weight;
};

void createAdjacencyMatrices(int numVertices, struct Edge* edges, int numEdges,
                              int*** successorMatrix, int*** predecessorMatrix) {
    int i;

    // Allocate memory for matrices
    *successorMatrix = (int**)malloc(numVertices * sizeof(int*));
    *predecessorMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (i = 0; i < numVertices; ++i) {
        (*successorMatrix)[i] = (int*)calloc(numVertices, sizeof(int));
        (*predecessorMatrix)[i] = (int*)calloc(numVertices, sizeof(int));
    }

    // Fill matrices
    for (i = 0; i < numEdges; ++i) {
        int from = edges[i].from;
        int to = edges[i].to;
        int weight = edges[i].weight;

        (*successorMatrix)[from][to] = weight;
        (*predecessorMatrix)[to][from] = weight;
    }
}

void printMatrix(int** matrix, int size, const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int numVertices = 4;
    struct Edge edges[] = {
        {0, 1, 2},
        {1, 2, 3},
        {2, 0, 4},
        {3, 2, 1}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    int** successors;
    int** predecessors;

    createAdjacencyMatrices(numVertices, edges, numEdges, &successors, &predecessors);

    printMatrix(successors, numVertices, "Successor Matrix");
    printMatrix(predecessors, numVertices, "Predecessor Matrix");

    freeMatrix(successors, numVertices);
    freeMatrix(predecessors, numVertices);

    return 0;
}