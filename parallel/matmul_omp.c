#include <stdio.h>
#include <stdlib.h>

#include <omp.h>


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

void multiply(const int ** const a, const int ** const b, int ** const ab,
              size_t m, size_t n, size_t p)
{
  for (size_t i = 0UL; i < m; ++i)
  {
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

void initialize(int ** const matrix, size_t m, size_t n)
{
#pragma omp for
  for (size_t i = 0UL; i < n; ++i)
  {
    for (size_t j = 0UL; j < m; ++j)
    {
      matrix[i][j] = i * j;
    }
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
#pragma omp for
  for (size_t i = 0UL; i < n; ++i)
  {
    free((int**)matrix[i]);
  }
  free((int*)matrix);
}

int main(void)
{
  const size_t SIZE_M = 10UL;
  const size_t SIZE_N = SIZE_M;
  const size_t SIZE_P = SIZE_M;

  int ** matA = allocateMatrix(SIZE_M, SIZE_N);
  int ** matB = allocateMatrix(SIZE_P, SIZE_M);
  int ** matC = allocateMatrix(SIZE_P, SIZE_N);
  
  initialize(matA, SIZE_M, SIZE_N);
  initialize(matB, SIZE_M, SIZE_N);
  
  printf("A: \n");
  printMatrix((const int ** const)matA, SIZE_M, SIZE_N);
  printf("B: \n");
  printMatrix((const int ** const)matB, SIZE_M, SIZE_N);
  
  printf("Shifting...\n");
#pragma omp for
  for (size_t i = 0UL; i < SIZE_N; ++i)
  {
    shiftRow(matA, SIZE_M, i, i);
  }
#pragma omp for
  for (size_t i = 0UL; i < SIZE_M; ++i)
  {
    shiftColumn(matB, SIZE_N, i, i);
  }
  
  printf("A: \n");
  printMatrix((const int ** const)matA, SIZE_M, SIZE_N);
  printf("B: \n");
  printMatrix((const int ** const)matB, SIZE_M, SIZE_N);

  freeMatrix(matB, SIZE_N);
  freeMatrix(matA, SIZE_N);
  
  return EXIT_SUCCESS;
}

