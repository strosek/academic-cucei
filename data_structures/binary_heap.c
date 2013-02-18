/*
 * Copyright (c) 2013 Erick Daniel Corona <edcoronag@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the Software), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
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
        heap_insert(heap, &depth, rand() % 100, nodeSetFlags);

    heap_print(heap, k_maxHeapSize);
    
    return EXIT_SUCCESS;
}

void heap_insert(int* const heap, int* depth, int element, Bool_t* nodeSetFlags) {
    if ((*depth) < 0) {
        (*depth) = 0;
    }
    int levelFirst = intPower(2, (*depth)) - 1;
    int levelLast = intPower(2, (*depth) + 1) - 2;

    int insertPosition;
    int i;
    Bool_t isSpaceFound = FALSE;
    for (i = levelFirst; i <= levelLast && !isSpaceFound; ++i)
        if (nodeSetFlags[i] == FALSE) {
            heap[i] = element;
            isSpaceFound = TRUE;
            nodeSetFlags[i] = TRUE;
            insertPosition = i;
        }

    if (!isSpaceFound) {
        ++(*depth);
        insertPosition = i;
        heap[insertPosition] = element;
        nodeSetFlags[insertPosition] = TRUE;
    }
    
    int currentLevel = (*depth);
    int parent, parentLevelFirst, currentLevelDisplacement;
    Bool_t isInPlace = FALSE;
    while (!isInPlace) {
        if (currentLevel == 0)
            isInPlace = TRUE;
        else {
            parentLevelFirst = (intPower(2, currentLevel - 1) - 1);
            currentLevelDisplacement = (insertPosition - (intPower(2, currentLevel) - 1));
            parent = parentLevelFirst + (currentLevelDisplacement / 2);
            if (heap[insertPosition] >= heap[parent])
                isInPlace = TRUE;
            else {
                swap(heap, insertPosition, parent);
                insertPosition = parent;
                --currentLevel;
            }
        }
    }
}

void heap_print(int* const heap, int nNodes) {
    if (nNodes > 0) {
        int i;
        int level = 0;
        printf("%5d nodes:\n\n", nNodes);
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
