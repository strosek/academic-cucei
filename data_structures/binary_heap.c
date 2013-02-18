#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {FALSE = 0, TRUE} Bool_t;

const int k_maxHeapSize = 15;

int  intPower(int a, int b);
void swap(int* const heap, int a, int b);
void heap_insert(int* const heap, int* depth, int element, Bool_t* nodeSetFlags);
void heap_print(int* const heap, int nNodes);


int main(void) {
    int heap[k_maxHeapSize];
    Bool_t nodeSetFlags[k_maxHeapSize];
    int i = 0;
    for (i = 0; i < k_maxHeapSize; ++i) {
        heap[i] = 0;
        nodeSetFlags[i] = FALSE;
    }
    int depth = -1;    

    srand(time(NULL));
    for (i = 0; i < k_maxHeapSize; ++i)
        heap_insert(heap, &depth, rand() % 20, nodeSetFlags);

    heap_print(heap, k_maxHeapSize);
    
    return EXIT_SUCCESS;
}

void heap_insert(int* const heap, int* depth, int element, Bool_t* nodeSetFlags) {
    if ((*depth) < 0) {
        (*depth) = 0;
    }
    int levelFirst = intPower(2, (*depth)) - 1;
    int levelLast = intPower(2, (*depth) + 1) - 2;

    int space;
    int i;
    Bool_t isSpaceFound = FALSE;
    printf("%d %d\n", levelFirst, levelLast);
    for (i = levelFirst; i <= levelLast && !isSpaceFound; ++i)
        if (nodeSetFlags[i] == FALSE) {
            heap[i] = element;
            isSpaceFound = TRUE;
            nodeSetFlags[i] = TRUE;
            space = i;
        }

    if (!isSpaceFound) {
        ++(*depth);
        space = i + 1;
        heap[space] = element;
    }
    
    int currentLevel = (*depth);
    int parent;
    Bool_t isInPlace = FALSE;
    while (!isInPlace) {
        if (currentLevel == 0)
            isInPlace = TRUE;
        else {
            parent = (intPower(2, (currentLevel) - 1) -1) +
                    (space - intPower(2, currentLevel) - 1) / 2;
            if (heap[space] >= heap[parent])
                isInPlace = TRUE;
            else {
                swap(heap, space, parent);
                space = parent;
                --currentLevel;
            }
        }
    }
}

void heap_print(int* const heap, int nNodes) {
    if (nNodes > 0) {
        int i;
        int level = 0;
        printf("%d nodes\n", nNodes);
        for (i = 0; i < nNodes; ++i) {
            printf("%5d ", heap[i]);
            if (i == intPower(2, level + 1) - 2) {
                printf("\n");
                ++level;
            }
        }
    }
    printf("\n");
}

int intPower(int a, int b) {
    if (a == 0)
        return 0;
    if (b == 0)
        return 1;
    
    int i;
    int result = 1;
    for (i = 0; i < b; ++i)
        result *= a;
    
    return result;
}

void swap(int* const heap, int a, int b) {
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
