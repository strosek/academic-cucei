// Test matrix operations

#include "matrix.h"

int main(void) {
  Matrix_t* point2d = allocMatrix(1, 3);
  Matrix_t* result2d = allocMatrix(1, 3); 
  
  // enter point 
  scanf("%f %f", &(point2d->data[0][0]), &(point2d->data[1][0]));
  point2d->data[2][0] = 1.0f;

  float tx, ty;
  // enter translation
  scanf("%f %f", &tx, &ty);

  printf("Original point: (%d,%d)\n\n", (int)roundf(point2d->data[0][0]),
                                                (int)roundf(point2d->data[1][0]));
  translation2d(point2d, result2d, tx, ty);
  printf("Point after translation: (%d,%d)\n", (int)roundf(result2d->data[0][0]),
                                               (int)roundf(result2d->data[1][0]));
  
  float theta;
  scanf("%f", &theta);
  rotation2d(point2d, result2d, theta);
  printf("Point after rotation: (%d,%d)\n", (int)roundf(result2d->data[0][0]),
                                            (int)roundf(result2d->data[1][0]));

  float sx, sy;
  scanf("%f %f", &sx, &sy);
  scale2d(point2d, result2d, sx, sy);
  printf("Point after scaling: (%d,%d)\n", (int)roundf(result2d->data[0][0]),
                                           (int)roundf(result2d->data[1][0]));

  freeMatrix(point2d);
  freeMatrix(result2d);
  
  return EXIT_SUCCESS;
}
