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

#define PI 3.14159

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
  for (i = 0; i < matrix->rows; ++i)
    free(matrix->data[i]);
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
      fprintf(stderr, "multiplyMatrices: error: size of matrices is not valid");
    }
  }
  else {
    fprintf(stderr, "multiplyMatrices: error: size of result matrix is not valid");
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
      fprintf(stderr, "sumMatrices: error: size of matrices is not valid");
    }
  }
  else {
    fprintf(stderr, "sumMatrices: error: size of result matrix is not valid");
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

void rotation2dWithPivot(Matrix_t* vector, Matrix_t* pivot, Matrix_t* result, float theta) {
  rotation2d(vector, result, theta);
  sumMatrices(result, pivot, result);
}

void scale2dFixedPoint(Matrix_t* vector, Matrix_t* fixedPoint, Matrix_t* result, float sx, float sy) {
  scale2d(vector, result, sx, sy);
  sumMatrices(result, fixedPoint, result);
}

void reflectionX2d(Matrix_t* vector, Matrix_t* result) {
  Matrix_t* reflectionMatrix = allocMatrix(3, 3);
  reflectionMatrix->data[0][0] =  1.0f;
  reflectionMatrix->data[0][1] =  0.0f;
  reflectionMatrix->data[0][2] =  0.0f;
  reflectionMatrix->data[1][0] =  0.0f;
  reflectionMatrix->data[1][1] = -1.0f;
  reflectionMatrix->data[1][2] =  0.0f;
  reflectionMatrix->data[2][0] =  0.0f;
  reflectionMatrix->data[2][1] =  0.0f;
  reflectionMatrix->data[2][2] =  1.0f;

  multiplyMatrices(reflectionMatrix, vector, result);

  freeMatrix(reflectionMatrix);
}

void reflectionY2d(Matrix_t* vector, Matrix_t* result) {
  Matrix_t* reflectionMatrix = allocMatrix(3, 3);
  reflectionMatrix->data[0][0] = -1.0f;
  reflectionMatrix->data[0][1] =  0.0f;
  reflectionMatrix->data[0][2] =  0.0f;
  reflectionMatrix->data[1][0] =  0.0f;
  reflectionMatrix->data[1][1] =  1.0f;
  reflectionMatrix->data[1][2] =  0.0f;
  reflectionMatrix->data[2][0] =  0.0f;
  reflectionMatrix->data[2][1] =  0.0f;
  reflectionMatrix->data[2][2] =  1.0f;

  multiplyMatrices(reflectionMatrix, vector, result);

  freeMatrix(reflectionMatrix);
}

void reflectionXY2d(Matrix_t* vector, Matrix_t* result) {
  Matrix_t* reflectionMatrix = allocMatrix(3, 3);
  reflectionMatrix->data[0][0] = -1.0f;
  reflectionMatrix->data[0][1] =  0.0f;
  reflectionMatrix->data[0][2] =  0.0f;
  reflectionMatrix->data[1][0] =  0.0f;
  reflectionMatrix->data[1][1] = -1.0f;
  reflectionMatrix->data[1][2] =  0.0f;
  reflectionMatrix->data[2][0] =  0.0f;
  reflectionMatrix->data[2][1] =  0.0f;
  reflectionMatrix->data[2][2] =  1.0f;

  multiplyMatrices(reflectionMatrix, vector, result);

  freeMatrix(reflectionMatrix);
}

void reflectionYeX2d(Matrix_t* vector, Matrix_t* result) {
  Matrix_t* reflectionMatrix = allocMatrix(3, 3);
  reflectionMatrix->data[0][0] =  0.0f;
  reflectionMatrix->data[0][1] =  1.0f;
  reflectionMatrix->data[0][2] =  0.0f;
  reflectionMatrix->data[1][0] =  1.0f;
  reflectionMatrix->data[1][1] =  0.0f;
  reflectionMatrix->data[1][2] =  0.0f;
  reflectionMatrix->data[2][0] =  0.0f;
  reflectionMatrix->data[2][1] =  0.0f;
  reflectionMatrix->data[2][2] =  1.0f;

  multiplyMatrices(reflectionMatrix, vector, result);

  freeMatrix(reflectionMatrix);
}

void reflectionYmX2d(Matrix_t* vector, Matrix_t* result) {
  Matrix_t* reflectionMatrix = allocMatrix(3, 3);
  reflectionMatrix->data[0][0] =  0.0f;
  reflectionMatrix->data[0][1] = -1.0f;
  reflectionMatrix->data[0][2] =  0.0f;
  reflectionMatrix->data[1][0] = -1.0f;
  reflectionMatrix->data[1][1] =  0.0f;
  reflectionMatrix->data[1][2] =  0.0f;
  reflectionMatrix->data[2][0] =  0.0f;
  reflectionMatrix->data[2][1] =  0.0f;
  reflectionMatrix->data[2][2] =  1.0f;

  multiplyMatrices(reflectionMatrix, vector, result);

  freeMatrix(reflectionMatrix);
}

void reflectionGeneral(Matrix_t* point, Matrix_t* result, float m, float b) {
  Matrix_t* temporal = allocMatrix(1, 3);
  Matrix_t* temporal2 = allocMatrix(1, 3);
  Matrix_t* temporal3 = allocMatrix(1, 3);
  translation2d(point, temporal, -b);
  rotation2d(temporal, temporal2, atanf(m / 1.0f));
  reflectionX2d(temporal2, temporal3);
  rotation2d(temporal3, result, -atanf(m / 1.0f));

  freeMatrix(temporal);
  freeMatrix(temporal2);
  freeMatrix(temporal3);
}

void rotation3dX(Matrix_t* vector, Matrix_t* result, float theta) {
  Matrix_t* rotationMatrix = allocMatrix(3, 3);
  rotationMatrix->data[0][0] = 1.0f;
  rotationMatrix->data[0][1] = 0.0f;
  rotationMatrix->data[0][2] = 0.0f;
  rotationMatrix->data[1][0] = 0.0f;
  rotationMatrix->data[1][1] = cosf(theta);
  rotationMatrix->data[1][2] = -sinf(theta);
  rotationMatrix->data[2][0] = 0.0f;
  rotationMatrix->data[2][1] = sinf(theta);
  rotationMatrix->data[2][2] = cos(theta);

  multiplyMatrices(rotationMatrix, vector, result);

  freeMatrix(rotationMatrix);
}

void rotation3dY(Matrix_t* vector, Matrix_t* result, float theta) {
  Matrix_t* rotationMatrix = allocMatrix(3, 3);
  rotationMatrix->data[0][0] = cosf(theta);
  rotationMatrix->data[0][1] = 0.0f;
  rotationMatrix->data[0][2] = sinf(theta);
  rotationMatrix->data[1][0] = 0.0f;
  rotationMatrix->data[1][1] = 1.0f;
  rotationMatrix->data[1][2] = 0.0f;
  rotationMatrix->data[2][0] = -sinf(theta);
  rotationMatrix->data[2][1] = 0.0f;
  rotationMatrix->data[2][2] = cosf(theta);

  multiplyMatrices(rotationMatrix, vector, result);

  freeMatrix(rotationMatrix);
}

void rotation3dZ(Matrix_t* vector, Matrix_t* result, float theta) {
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

float getRadians(float degrees) {
  return degrees * PI / 180.0f;
}

void projection(Matrix_t* vector, Matrix_t* result) {
  Matrix_t* projectionMatrix = allocMatrix(3, 3);
  projectionMatrix->data[0][0] = 1.0f;
  projectionMatrix->data[0][1] = 0.0f;
  projectionMatrix->data[0][2] = 0.0f;
  projectionMatrix->data[1][0] = 0.0f;
  projectionMatrix->data[1][1] = 1.0f;
  projectionMatrix->data[1][2] = 0.0f;
  projectionMatrix->data[2][0] = 0.0f;
  projectionMatrix->data[2][1] = 0.0f;
  projectionMatrix->data[2][2] = 0.0f;

  multiplyMatrices(projectionMatrix, vector, result);

  freeMatrix(projectionMatrix);
}
#endif // matrix.h included

