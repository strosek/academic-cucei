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

const int k_maxWeightDigits = 20;

int** newGraphMatrix(int nVertices);
void deleteGraphMatrix(int** const graph);
void printGraph(int** const graph, int nVertices);

void bfs(int** const graph, int nVertices, int rootVertex);
void dfs(int** const graph, int nVertices, int rootVertex);
void prim(int** const graph, int nVertices);
void kruskal(int** const graph, int nVertices);


int main(void) {
    int nVertices;
    scanf("%d", &nVertices);

    int** graph = newGraphMatrix(nVertices);

    int i, j;
    int edgeWeight;
    char edgeWeightString[k_maxWeightDigits];
    for (i = 0; i < nVertices; ++i) {
        j = 0;
        while (j < nVertices) {
            scanf("%s", edgeWeightString);
            if (edgeWeightString[0] == '*') {
                edgeWeight = INT_MAX;
            }
            else {
                sscanf(edgeWeightString, "%d", &edgeWeight);
            }
            graph[i][j] = edgeWeight;
            ++j;
        }
    }

    printf("Graph edges:\n\n");
    printGraph(graph, nVertices);

    printf("\nBreadth-First Search: \n\n");
    int rootVertex;
    for (rootVertex = 0; rootVertex < nVertices; ++rootVertex) {
        bfs(graph, nVertices, rootVertex);
    }

    printf("\nDepth-First Search: \n\n");
    for (rootVertex = 0; rootVertex < nVertices; ++rootVertex) {
        dfs(graph, nVertices, rootVertex);
    }
    
    printf("\nMinimum Spanning Tree (Prim's algorithm):\n\n");
    prim(graph, nVertices);

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

void deleteGraphMatrix(int** const graph) {
    free(graph);
}

void printGraph(int** const graph, int nVertices) {
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

void bfs(int** const graph, int nVertices, int rootVertex) {
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

void dfs(int** const graph, int nVertices, int rootVertex) {
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

void prim(int** const graph, int nVertices) {
    Bool_t* visitedFlags = (Bool_t*)malloc(sizeof(Bool_t) * nVertices);
    Bool_t* openVerticesFlags = (Bool_t*)malloc(sizeof(Bool_t) * nVertices);
    int i, j;
    for (i = 0; i < nVertices; ++i) {
        visitedFlags[i] = FALSE;
        openVerticesFlags[i] = FALSE;
    }
    
    int visitedVertices = 0;
    
    visitedFlags[0] = TRUE;
    openVerticesFlags[0] = TRUE;
    ++visitedVertices;
    int minEdge = INT_MAX;
    int minEdgeOrigin = 0, minEdgeDestiny = 0;
    Bool_t isPossibleEdgeFound = TRUE;
    while (isPossibleEdgeFound && visitedVertices < nVertices) {
        isPossibleEdgeFound = FALSE;
        minEdge = INT_MAX;
        for (i = 0; i < nVertices; ++i) {
            if (openVerticesFlags[i] == TRUE) {
                for (j = 0; j < nVertices; ++j) {
                    if (graph[i][j] != INT_MAX && visitedFlags[j] == FALSE) {
                        isPossibleEdgeFound = TRUE;
                        if (graph[i][j] < minEdge) {
                            minEdge = graph[i][j];
                            minEdgeOrigin = i;
                            minEdgeDestiny = j;
                        }
                    }
                }
                if (!isPossibleEdgeFound) {
                    openVerticesFlags[i] = FALSE;
                }
            }
        }
        if (isPossibleEdgeFound) {
            openVerticesFlags[minEdgeDestiny] = TRUE;
            visitedFlags[minEdgeDestiny] = TRUE;
            printf("%d-%d, %d\n", minEdgeOrigin, minEdgeDestiny, minEdge);
        }
    }

    free(visitedFlags);
    free(openVerticesFlags);
}
