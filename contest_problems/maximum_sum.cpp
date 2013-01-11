//  Copyright (c) 2012 Erick Daniel Corona <edcoronag@gmail.com>
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without
//  restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following
//  conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

// Solution to
// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=44s

#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;


inline int sumSubrectangle(int** matrix, int begX, int begY, int endX, int endY); // Optimized
inline int sumRectangle(int** matrix, int begX, int begY, int endX, int endY);

int main(void) {
    int matrixSize;
    cin >> matrixSize;

    int** matrix = (int**)malloc(sizeof(int*) * matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        matrix[i] = (int*)malloc(sizeof(int) * matrixSize);
    }
    
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            cin >> matrix[i][j];
        }
    }

    int maxSum = numeric_limits<int>::min();
    int sum;

    int begX, begY, endX, endY;
    for (begY = 0; begY < matrixSize; ++begY) {
        for (begX = 0; begX < matrixSize; ++begX) {
            for (endY = begY; endY < matrixSize; ++endY) {
                for (endX = begX; endX < matrixSize; ++endX) {
                    sum = sumSubrectangle(matrix, begX, begY, endX, endY);
                    if (sum > maxSum) {
                        maxSum = sum;
                    }
                }
            }
        }
    }

    cout << maxSum << endl;

    return EXIT_SUCCESS;
}

inline int sumSubrectangle(int** matrix, int begX, int begY, int endX, int endY) {
    static int sum;
    static int previousEndX, previousEndY;
    static int previousSum;

    if (endX > previousEndX && endY == previousEndY) {
        sum = previousSum + sumRectangle(matrix, endX, begY, endX, endY);
    }
    else {
        sum = sumRectangle(matrix, begX, begY, endX, endY);
    }
    previousEndX = endX;
    previousEndY = endY;
    previousSum = sum;

    return sum;
}

inline int sumRectangle(int** matrix, int begX, int begY, int endX, int endY) {
    static int sum;
    int i, j;

    sum = 0;
    for (i = begY; i <= endY; ++i) {
        for (j = begX; j <= endX; ++j) {
            sum += matrix[i][j];
        }
    }

    return sum;
}
