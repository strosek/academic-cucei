// Test different point transforms

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

int main(void) {
  int x, y, z;
  Matrix_t* point = allocMatrix(1, 3);
  Matrix_t* result = allocMatrix(1, 3);
  Matrix_t* fixed = allocMatrix(1, 3);

  int transformType = 0;
  printf("Enter transform type : ");
  scanf("%d", &transformType);

  int fx, fy, fz;
  printf("Enter fixed/pivot point: ");
  scanf("%d %d %d", &fx, &fy, &fz);
  fixed->data[0][0] = fx;
  fixed->data[1][0] = fy;
  fixed->data[2][0] = fz;

  float theta;
  printf("Enter angle: ");
  scanf("%f", &theta);
  theta = getRadians(theta);

  float tsX, tsY, tsZ;
  printf("Enter transform values: ");
  scanf("%f %f %f", &tsX, &tsY, &tsZ);

  printf("Enter points (x, y, z) :\n");
  while (!feof(stdin)) {
    scanf("%d %d %d", &x, &y, &z);
    point->data[0][0] = x;
    point->data[1][0] = y;
    point->data[2][0] = z;

    switch (transformType) {
      case 0 :
        translation2d(point, result, tsX, tsY);
        break;
      case 1 :
        rotation2d(point, result, theta);
        break;
      case 2 :
        scale2d(point, result, tsX, tsY);
        break;
      case 3 :
        rotation2dWithPivot(point, fixed, result, theta);
        break;
      case 4 :
        scale2dFixedPoint(point, fixed, result, tsX, tsY);
        break;
      case 5 :
        reflectionX2d(point, result);
        break;
      case 6 :
        reflectionY2d(point, result);
        break;
      case 7 :
        reflectionXY2d(point, result);
        break;
      case 8 :
        reflectionYeX2d(point, result);
        break;
      case 9 :
        reflectionYmX2d(point, result);
        break;
      case 10 :
        rotation3dX(point, result, theta);
        break;
      case 11 :
        rotation3dY(point, result, theta);
        break;
      case 12 :
        rotation3dZ(point, result, theta);
        break;
      default :
        printf("Bad transform type.\n");
        break;
    }
    printf("(%d,%d,%d), ", (int)roundf(result->data[0][0]),
                           (int)roundf(result->data[1][0]),
                           (int)roundf(result->data[2][0]));
  }

  freeMatrix(point); 
  return EXIT_SUCCESS; 
}


