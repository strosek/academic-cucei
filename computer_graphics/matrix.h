// Library for manipulating simple matrices.

#ifndef matrix_H
#define matrix_H

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct matrix {
  size_t cols;
  size_t rows;
  float**  data;
} Matrix_t;


Matrix_t* allocMatrix(size_t cols, size_t rows) {
  Matrix_t* matrix = (Matrix_t*)malloc(sizeof(Matrix_t));
  matrix->cols = cols;
  matrix->rows = rows;

  matrix->data = (float**)malloc(sizeof(float*) * rows);
  size_t i;
  for (i = 0; i < rows; ++i)
    matrix->data[i] = (float*)malloc(sizeof(float) * cols);
  
  return matrix;
}

void freeMatrix(Matrix_t* matrix) {
  size_t i;
  for (i = 0; i < matrix->rows; ++i) {
    free(matrix->data[i]);
  }

  free(matrix);
}

void multiplyMatrices(Matrix_t* a, Matrix_t* b, Matrix_t* result) {
  if (result->cols == b->cols && result->rows == a->rows) {
    if (a->cols == b->rows) {
      size_t i, j, k;
      for (i = 0; i < result->rows; ++i) {
        for (j = 0; j < result->cols; ++j) {
          for (k = 0; k < a->cols; ++k) {
            result->data[i][j] += a->data[i][k] * b->data[k][j];
          }
        }
      }
    }
    else {
      fprintf(stderr, "size of matrices is not valid");
    }
  }
  else {
    fprintf(stderr, "size of result matrix is not valid");
  }
}

void printMatrix(Matrix_t* matrix) {
  size_t i, j;
  for (i = 0; i < matrix->rows; ++i) {
    for (j = 0; j < matrix->cols; ++j) {
      printf("%.2f   ", matrix->data[i][j]);
    }
    printf("\n");
  }
}

#endif // matrix.h included

