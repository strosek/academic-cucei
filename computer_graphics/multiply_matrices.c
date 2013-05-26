#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


int main(void) {
  Matrix_t* matA;
  Matrix_t* matB;
  Matrix_t* matC;
  size_t mA = 0, mB = 0, nA = 0, nB = 0;

  scanf("%lu %lu", &mA, &nA);
  scanf("%lu %lu", &mB, &nB);

  matA = allocMatrix(mA, nA);
  matB = allocMatrix(mB, nB);

  size_t i, j;
  for (i = 0; i < matA->rows; ++i)
    for (j = 0; j < matA->cols; ++j)
      scanf("%f", &(matA->data[i][j]));

  for (i = 0; i < matB->rows; ++i)
    for (j = 0; j < matB->cols; ++j) {
      scanf("%f", &(matB->data[i][j]));
    }
  

  matC = allocMatrix(matB->cols, matA->rows);

  multiplyMatrices(matA, matB, matC);

  printMatrix(matC);
  
  freeMatrix(matA);
  freeMatrix(matB);
  freeMatrix(matC);

  return EXIT_SUCCESS;
}

