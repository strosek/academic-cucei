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
#include <string.h>

typedef enum Bool {FALSE = 0, TRUE} Bool_t;

typedef struct edge {
    int weight;
    int source;
    int destination;
} Edge_t;

const int MAX_WEIGHT_DIGITS = 20;
const int INFINITY = INT_MAX;

int** newGraphMatrix(int nVertices);
void deleteGraphMatrix(int** const graph, int nVertices);
void printGraph(int** const graph, int nVertices);

void bfs(int** const graph, int nVertices, int rootVertex);
void dfs(int** const graph, int nVertices, int rootVertex);
void prim(int** const graph, int nVertices);
void kruskal(int** const graph, int nVertices);
void dijkstra(int** const graph, int nVertices, int initialVertex);
void bellman_ford(int** const graph, int nVertices, int initialVertex);

int compareEdges(const void* edge1, const void* edge2);

int main(void) {
    int nVertices;
    scanf("%d", &nVertices);

    int** graph = newGraphMatrix(nVertices);

    int i, j;
    int edgeWeight;
    char edgeWeightString[MAX_WEIGHT_DIGITS];
    for (i = 0; i < nVertices; ++i) {
        j = 0;
        while (j < nVertices) {
            scanf("%s", edgeWeightString);
            if (edgeWeightString[0] == '*') {
                edgeWeight = INFINITY;
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

    printf("\nMinimum Spanning Tree/Forest (Kruskal's algorithm):\n\n");
    kruskal(graph, nVertices);

    printf("\nShortest paths from an edge (Dijkstra's algorithm):\n\n");
    dijkstra(graph, nVertices, 0);

    printf("\nShortest paths from an edge (Bellman-Ford algorithm):\n\n");
    bellman_ford(graph, nVertices, 0);

    deleteGraphMatrix(graph, nVertices);

    return EXIT_SUCCESS;
}

int** newGraphMatrix(int nVertices) {
    int** const graph = (int**)calloc(nVertices, sizeof(int*));
    int i, j;
    for (i = 0; i < nVertices; ++i) {
        graph[i] = (int*)calloc(nVertices, sizeof(int));
        for (j = 0; j < nVertices; ++j) {
            graph[i][j] = INFINITY;
        }
    }

    return graph;
}

void deleteGraphMatrix(int** const graph, int nVertices) {
    int i;
    for (i = 0; i < nVertices; ++i) {
        free(graph[i]);
    }
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
            if (graph[i][j] != INFINITY) {
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
    int* const queue = (int*)calloc(nVertices, sizeof(int));
    int front, back;

    Bool_t* const visitedFlags = (Bool_t*)calloc(nVertices, sizeof(Bool_t));
    memset(visitedFlags, FALSE, sizeof(Bool_t) * nVertices);

    front = back = 0;
    queue[back] = rootVertex;
    visitedFlags[rootVertex] = TRUE;
    printf("%d ", rootVertex);

    int i;
    while (front <= back) {
        for (i = 0; i < nVertices; ++i) {
            if (graph[queue[front]][i] != INFINITY && visitedFlags[i] == FALSE) {
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
    int* const stack = (int*)calloc(nVertices, sizeof(int));
    int top;

    Bool_t* const visitedFlags = (Bool_t*)calloc(nVertices, sizeof(Bool_t));
    int i;
    memset(visitedFlags, FALSE, sizeof(Bool_t) * nVertices);

    top = 0;
    stack[top] = rootVertex;
    visitedFlags[rootVertex] = TRUE;
    printf("%d ", rootVertex);

    Bool_t isChildFound;
    while (top >= 0) {
        isChildFound = FALSE;
        for (i = 0; i < nVertices && !isChildFound; ++i) {
            if (graph[stack[top]][i] != INFINITY && visitedFlags[i] == FALSE) {
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
    Bool_t* const visitedFlags = (Bool_t*)calloc(nVertices, sizeof(Bool_t));
    Bool_t* const openVerticesFlags = (Bool_t*)calloc(nVertices, sizeof(Bool_t));

    memset(visitedFlags, FALSE, sizeof(Bool_t) * nVertices);
    memset(openVerticesFlags, FALSE, sizeof(Bool_t) * nVertices);
    
    int visitedVertices = 0;
    
    visitedFlags[0] = TRUE;
    openVerticesFlags[0] = TRUE;
    ++visitedVertices;

    int i, j;
    Edge_t minEdge;
    Bool_t isPossibleEdgeFound = TRUE;
    while (isPossibleEdgeFound && visitedVertices < nVertices) {
        isPossibleEdgeFound = FALSE;
        minEdge.weight = INFINITY;
        for (i = 0; i < nVertices; ++i) {
            if (openVerticesFlags[i] == TRUE) {
                for (j = 0; j < nVertices; ++j) {
                    if (graph[i][j] != INFINITY && visitedFlags[j] == FALSE) {
                        isPossibleEdgeFound = TRUE;
                        if (graph[i][j] < minEdge.weight) {
                            minEdge.weight = graph[i][j];
                            minEdge.source = i;
                            minEdge.destination = j;
                        }
                    }
                }
                if (!isPossibleEdgeFound) {
                    openVerticesFlags[i] = FALSE;
                }
            }
        }
        if (isPossibleEdgeFound) {
            openVerticesFlags[minEdge.destination] = TRUE;
            visitedFlags[minEdge.destination] = TRUE;
            printf("%d-%d, %d\n", minEdge.source, minEdge.destination, minEdge.weight);
        }
    }

    free(visitedFlags);
    free(openVerticesFlags);
}

int compareEdges(const void* edge1, const void* edge2) {
    return ((Edge_t*)edge1)->weight - ((Edge_t*)edge2)->weight;
}

void kruskal(int** const graph, int nVertices) {
    const int maxEdges = nVertices * (nVertices - 1) / 2;
    Edge_t* const edges = (Edge_t*)calloc(maxEdges, sizeof(Edge_t));

    int i, j;
    int edgeNo = 0;
    for (i = 0; i < nVertices; ++i) {
        for (j = 0; j < nVertices; ++j) {
            if (graph[i][j] != INFINITY) {
                edges[edgeNo].weight = graph[i][j];
                edges[edgeNo].source = i;
                edges[edgeNo].destination = j;
                ++edgeNo;
            }
        }
    }
    int nEdges = edgeNo;

    qsort(edges, nEdges, sizeof(Edge_t), compareEdges);

    Bool_t* const visitedFlags = (Bool_t*)calloc(nVertices, sizeof(Bool_t));
    memset(visitedFlags, FALSE, sizeof(Bool_t) * nVertices);

    for (i = 0; i < nEdges; ++i) {
        if (visitedFlags[edges[i].destination] == FALSE) {
            visitedFlags[edges[i].source] = TRUE;
            visitedFlags[edges[i].destination] = TRUE;
            printf("%d-%d, %d\n", edges[i].source, edges[i].destination, edges[i].weight);
        }
    }

//     free(visitedFlags);
//     free(edges);
}

void dijkstra(int** const graph, int nVertices, int initialVertex) {
    int* const distances = (int*)calloc(nVertices, sizeof(int));
    int* const previousVertices = (int*)calloc(nVertices, sizeof(int));
    int* const queue = (int*)calloc(nVertices, sizeof(int));
    Bool_t* const visitedFlags = (Bool_t*)calloc(nVertices, sizeof(Bool_t));
    memset(visitedFlags, FALSE, sizeof(Bool_t) * nVertices);

    int i;
    for (i = 0; i < nVertices; ++i) {
        distances[i] = INFINITY;
    }
    

    int front, back;

    front = back = 0;
    queue[back] = initialVertex;
    previousVertices[initialVertex] = initialVertex;
    distances[initialVertex] = 0;

    int currentVertex = initialVertex;
    int distance;
    while (front <= back) {
        for (i = 0; i < nVertices; ++i) {
            currentVertex = queue[front];
            if (graph[currentVertex][i] != INFINITY && visitedFlags[i] == FALSE) {
                ++back;
                queue[back] = i;
                distance = graph[currentVertex][i] + distances[currentVertex];
                if (distance < distances[i]) {
                    distances[i] = graph[currentVertex][i] + distances[currentVertex];
                    previousVertices[i] = currentVertex;
                }
            }
        }
        visitedFlags[currentVertex] = TRUE;
        ++front;
    }

    printf("  V Dist Prev\n");
    printf("--- ---- ----\n");
    for (i = 0; i < nVertices; ++i) {
        printf("%3d%5d%5d\n", i, distances[i], previousVertices[i]);
    }

//     free(visitedFlags);
//     free(queue);
//     free(previousVertices);
//     free(distances);
}

void bellman_ford(int** const graph, int nVertices, int initialVertex) {
    int* const distances = (int*)calloc(nVertices, sizeof(int));
    int* const previousVertices = (int*)calloc(nVertices, sizeof(int));
    const int maxEdges = nVertices * (nVertices - 1) / 2;
    Edge_t* const edges = (Edge_t*)calloc(maxEdges, sizeof(Edge_t));

    int i, j;
    for (i = 0; i < nVertices; ++i) {
        distances[i] = INFINITY;
    }

    distances[initialVertex] = 0;
    previousVertices[initialVertex] = initialVertex;
    
    int edgeNo = 0;
    for (i = 0; i < nVertices; ++i) {
        for (j = 0; j < nVertices; ++j) {
            if (graph[i][j] != INFINITY) {
                edges[edgeNo].weight = graph[i][j];
                edges[edgeNo].source = i;
                edges[edgeNo].destination = j;
                if (distances[edges[edgeNo].source] != INFINITY) {
                    if (distances[edges[edgeNo].source] + edges[edgeNo].weight <
                            distances[edges[edgeNo].destination]) {
                        distances[edges[edgeNo].destination] = distances[edges[edgeNo].source] +
                                edges[edgeNo].weight;
                        previousVertices[edges[edgeNo].destination] = edges[edgeNo].source;
                    }
                }
                ++edgeNo;
            }
        }
    }
    const int nEdges = edgeNo;

    Bool_t isNegativeCycleFound = FALSE;
    for (edgeNo = 0; edgeNo < nEdges && !isNegativeCycleFound; ++edgeNo) {
        if (distances[edges[edgeNo].source] + edges[edgeNo].weight <
                            distances[edges[edgeNo].destination]) {
            isNegativeCycleFound = TRUE;
        }
    }

    if (isNegativeCycleFound) {
        fprintf(stderr, "bellman_ford: negative-weight cycle found\n");
    }
    else {
        printf("  V Dist Prev\n");
        printf("--- ---- ----\n");
        for (i = 0; i < nVertices; ++i) {
            printf("%3d%5d%5d\n", i, distances[i], previousVertices[i]);
        }
    }

//     free(edges);
//     free(previousVertices);
//     free(distances);
}
