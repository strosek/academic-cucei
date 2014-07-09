/* Dynamic-sized matrix common operations implementation */

#include "matrix.h"

#include <stdio.h>
#include <string.h>


void shiftRow(int ** const matrix, size_t m, size_t row, size_t times)
{
  int aux;
  
  for (size_t i = 0UL; i < times; ++i)
  {
    aux = matrix[row][0UL];
    for (size_t j = 1UL; j < m; ++j)
    {
      matrix[row][j - 1UL] = matrix[row][j];
    }
    matrix[row][m - 1UL] = aux;
  }
}

void shiftColumn(int ** const matrix, size_t n, size_t column, size_t times)
{
  int aux;

  for (size_t i = 0UL; i < times; ++i)
  {
    aux = matrix[0UL][column];
    for (size_t j = 1UL; j < n; ++j)
    {
      matrix[j - 1UL][column] = matrix[j][column];
    }
    matrix[n - 1UL][column] = aux;
  }
}

void multiplyMatrices(const int ** const a, const int ** const b, int ** const ab,
              size_t size)
{
#pragma omp parallel for
  for (size_t i = 0UL; i < size; ++i)
  {
    for (size_t j = 0UL; j < size; ++j)
    {
      ab[i][j] = a[i][j] * b[i][j];
    }
  }
}

void printMatrix(const int ** const matrix, size_t m, size_t n)
{
  for (size_t i = 0UL; i < n; ++i)
  {
    for (size_t j = 0UL; j < m; ++j)
    {
      printf("%4i", matrix[i][j]);
    }
    printf("\n");
  }
}

void initializeMatrix(int ** const matrix, size_t m, size_t n)
{
#pragma omp parallel for
  for (size_t i = 0UL; i < n; ++i)
  {
    memset(matrix[i], 0U, sizeof(size_t) * m);
  }
}

int ** allocateMatrix(size_t m, size_t n)
{
  int ** matrix = (int**)malloc(sizeof(int*) * n);
  for (size_t i = 0UL; i < n; ++i)
  {
    matrix[i] = (int*)malloc(sizeof(int) * m);
  }

  return matrix;
}

void freeMatrix(int ** const matrix, size_t n)
{
#pragma omp parallel for
  for (size_t i = 0UL; i < n; ++i)
  {
    free((int**)matrix[i]);
  }
  free((int*)matrix);
}


