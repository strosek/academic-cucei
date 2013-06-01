// Library for manipulating simple matrices.

#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
  for (i = 0; i < rows; ++i)
    memset(matrix->data[i], 0, sizeof(float) * cols);
  
  return matrix;
}

void freeMatrix(Matrix_t* matrix) {
  size_t i;
  for (i = 0; i < matrix->rows; ++i) {
    free(matrix->data[i]);
  }
  free(matrix->data);

  free(matrix);
}

void multiplyMatrices(Matrix_t* a, Matrix_t* b, Matrix_t* result) {
  if (result->cols == b->cols && result->rows == a->rows) {
    if (a->cols == b->rows) {
      size_t i, j, k;
      for (i = 0; i < result->rows; ++i)
        memset(result->data[i], 0, sizeof(float) * result->cols);
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

void sumMatrices(Matrix_t* a, Matrix_t* b, Matrix_t* result) {
  if (result->cols == a->cols && result->rows == a->rows) {
    if (a->cols == b->cols && a->rows == b->rows) {
      size_t i, j;
      for (i = 0; i < result->rows; ++i) {
        for (j = 0; j < result->cols; ++j) {
          result->data[i][j] = a->data[i][j] + b->data[i][j];
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

void translation2d(Matrix_t* vector, Matrix_t* result, float tx, float ty) {
  Matrix_t* translationMatrix = allocMatrix(3, 3);
  translationMatrix->data[0][0] = 1.0f;
  translationMatrix->data[0][1] = 0.0f;
  translationMatrix->data[0][2] = tx;
  translationMatrix->data[1][0] = 0.0f;
  translationMatrix->data[1][1] = 1.0f;
  translationMatrix->data[1][2] = ty;
  translationMatrix->data[2][0] = 0.0f;
  translationMatrix->data[2][1] = 0.0f;
  translationMatrix->data[2][2] = 1.0f;

  multiplyMatrices(translationMatrix, vector, result);
  freeMatrix(translationMatrix);
}

void rotation2d(Matrix_t* vector, Matrix_t* result, float theta) {
  Matrix_t* rotationMatrix = allocMatrix(3, 3);
  rotationMatrix->data[0][0] = cosf(theta);
  rotationMatrix->data[0][1] = -sinf(theta);
  rotationMatrix->data[0][2] = 0.0f;
  rotationMatrix->data[1][0] = sinf(theta);
  rotationMatrix->data[1][1] = cosf(theta);
  rotationMatrix->data[1][2] = 0.0f;
  rotationMatrix->data[2][0] = 0.0f;
  rotationMatrix->data[2][1] = 0.0f;
  rotationMatrix->data[2][2] = 1.0f;

  multiplyMatrices(rotationMatrix, vector, result);
  freeMatrix(rotationMatrix);
}

void scale2d(Matrix_t* vector, Matrix_t* result, float sx, float sy) {
  Matrix_t* scaleMatrix = allocMatrix(3, 3);
  scaleMatrix->data[0][0] = sx;
  scaleMatrix->data[0][1] = 0.0f;
  scaleMatrix->data[0][2] = 0.0f;
  scaleMatrix->data[1][0] = 0.0f;
  scaleMatrix->data[1][1] = sy;
  scaleMatrix->data[1][2] = 0.0f;
  scaleMatrix->data[2][0] = 0.0f;
  scaleMatrix->data[2][1] = 0.0f;
  scaleMatrix->data[2][2] = 1.0f;

  multiplyMatrices(scaleMatrix, vector, result);
  freeMatrix(scaleMatrix);
}

#endif // matrix.h included

