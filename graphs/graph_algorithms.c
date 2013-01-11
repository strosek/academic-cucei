 /*
 *  Copyright (c) 2013 Erick Daniel Corona <edcoronag@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the Software), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum Bool {FALSE = 0, TRUE} Bool_t;

const int k_maxDigits = 20;

void printGraph(int** graph, int nVertices);
int** newGraphMatrix(int nVertices);
void deleteGraphMatrix(int** graph);
void bfs(int** graph, int nVertices, int rootVertex);
void dfs(int** graph, int nVertices, int rootVertex);


int main(void) {
    int nVertices;
    scanf("%d", &nVertices);

    int** graph = newGraphMatrix(nVertices);

    int i, j;
    int edgeWeight;
    char edgeWeightStirng[k_maxDigits];
    for (i = 0; i < nVertices; ++i) {
        j = 0;
        while (j < nVertices) {
            scanf("%s", edgeWeightString);
            if (edgeWeightString[0] == 'i') {
                edgeWeight = INT_MAX;
            }
            else {
                sscanf(edgeWeigthString, "%d", &edgeWeight);
            }
            graph[i][j] = edgeWeight;
            ++j;
        }
    }

    printf("Graph edges:\n\n");
    printGraph(graph, nVertices);

    printf("\nBreadth-First Search: \n\n");
    int rootVertex;
    scanf("%d", &rootVertex);
    bfs(graph, nVertices, rootVertex);

    printf("\nDepth-First Search: \n\n");
    scanf("%d", &rootVertex);
    dfs(graph, nVertices, rootVertex);

    deleteGraphMatrix(graph);

    return EXIT_SUCCESS;
}

int** newGraphMatrix(int nVertices) {
    int** graph = (int**)malloc(sizeof(int*) * nVertices);
    int i, j;
    for (i = 0; i < nVertices; ++i) {
        graph[i] = (int*)malloc(sizeof(int) * nVertices);
        for (j = 0; j < nVertices; ++j) {
            graph[i][j] = INT_MAX;
        }
    }

    return graph;
}

void deleteGraphMatrix(int** graph) {
    free(graph);
}

void printGraph(int** graph, int nVertices) {
    int i,j;

    printf("    ");
    for (i = 0; i < nVertices; ++i) {
        printf("%3d", i);
    }
    printf("\n");
    printf("    ");
    for (i = 0; i < nVertices; ++i) {
        printf("---");
    }
    printf("\n");

    for (i = 0; i < nVertices; ++i) {
        printf("%3d:", i);
        for (j = 0; j < nVertices; ++j) {
            if (graph[i][j] != INT_MAX) {
                printf("%3d", graph[i][j]);
            }
            else {
                printf("%3c", ' ');
            }
        }
        printf("\n");
    }
}

void bfs(int** graph, int nVertices, int rootVertex) {
    int* queue = (int*)malloc(sizeof(int) * nVertices);
    int front, back;

    Bool_t* visitedFlags = (Bool_t*)malloc(sizeof(Bool_t) * nVertices);
    int i;
    for (i = 0; i < nVertices; ++i) {
        visitedFlags[i] = FALSE;
    }

    front = back = 0;
    queue[back] = rootVertex;
    visitedFlags[rootVertex] = TRUE;
    printf("%d ", rootVertex);

    while (front <= back) {
        for (i = 0; i < nVertices; ++i) {
            if (graph[queue[front]][i] != INT_MAX && visitedFlags[i] == FALSE) {
                ++back;
                queue[back] = i;
                visitedFlags[i] = TRUE;
                printf("%d ", i);
            }
        }
        ++front;
    }
    printf("\n");

    free(queue);
    free(visitedFlags);
}

void dfs(int** graph, int nVertices, int rootVertex) {
    int* stack = (int*)malloc(sizeof(int) * nVertices);
    int top;

    Bool_t* visitedFlags = (Bool_t*)malloc(sizeof(Bool_t) * nVertices);
    int i;
    for (i = 0; i < nVertices; ++i) {
        visitedFlags[i] = FALSE;
    }

    top = 0;
    stack[top] = rootVertex;
    visitedFlags[rootVertex] = TRUE;
    printf("%d ", rootVertex);

    Bool_t isChildFound;
    while (top >= 0) {
        isChildFound = FALSE;
        for (i = 0; i < nVertices && !isChildFound; ++i) {
            if (graph[stack[top]][i] != INT_MAX && visitedFlags[i] == FALSE) {
                ++top;
                stack[top] = i;
                isChildFound = TRUE;
                visitedFlags[i] = TRUE;
                printf("%d ", i);
            }
        }
        if (!isChildFound) {
            --top;
        }
    }
    printf("\n");

    free(stack);
    free(visitedFlags);
}
