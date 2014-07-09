/* Dynamic-sized matrix common operations */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

int ** allocateMatrix(size_t m, size_t n);
void freeMatrix(int ** const matrix, size_t n);
void initializeMatrix(int ** const matrix, size_t m, size_t n);
void multiplyMatrices(const int ** const a, const int ** const b,
                      int ** const ab, size_t size);
void printMatrix(const int ** const matrix, size_t m, size_t n);
void shiftColumn(int ** const matrix, size_t n, size_t column, size_t times);
void shiftRow(int ** const matrix, size_t m, size_t row, size_t times);

#endif /* MATRIX_H defined */

