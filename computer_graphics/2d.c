#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(void) {
  int operationType = 0;
  while (operationType != 13) {
    printf("===================================================\n");
    printf("=============== TRANSFORMACIONES 2D ===============\n");
    printf("===================================================\n\n");
    
    printf("Elije operacion a realizar: \n\n");
    printf(
  "  1) Traslacion\n\
  2) Rotacion\n\
  3) Escalamiento\n\
  4) Rotacion c/pivote\n\
  5) Escalamiento c/ punto fijo\n\
  6) Reflexion eje X\n\
  7) Reflexion eje Y\n\
  8) Reflexion ejes YX\n\
  9) Reflexion eje Y = X\n\
 10) Reflexion linea paralela a XY en punto\n\
 11) Reflexion Y = -X\n\
 12) Reflexion Y = mX + b\n\
 13) Salir\t>> ");
    scanf("%d", &operationType);
    if (operationType == 13)
      break;
    
    
    Matrix_t* point = allocMatrix(1, 3);
    Matrix_t* result = allocMatrix(1, 3);
    Matrix_t* pf = allocMatrix(1, 3);
    int x, y, pfx, pfy;
    float tx, ty, sx, sy, m, b;
    float theta;
    int nPoints;
    int i;

    printf("Numero de puntos: ");
    scanf("%d", &nPoints);
    for (i = 0; i < nPoints; ++i) {
      switch (operationType) {
        case 1 :
          if (i == 0) {
            printf("Tx, Ty: ");
            scanf("%f %f", &tx, &ty);
            printf("Dame puntos:\n");
          }
          
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          
          translation2d(point, result, tx, ty);
          break;
        case 2 :
          if (i == 0) {
            printf("Theta: ");
            scanf("%f", &theta);
            printf("Dame puntos:\n");
          }
          
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          
          rotation2d(point, result, getRadians(theta));
          break;
        case 3 :
          if (i == 0) {
            printf("Sx, Sy: ");
            scanf("%f %f", &sx, &sy);
            printf("Dame puntos:\n");
          }
          
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          
          scale2d(point, result, sx, sy);
          break;
        case 4 :
          if (i == 0) {
            printf("Theta: ");
            scanf("%f", &theta);
            printf("Punto fijo: ");
            scanf("%d %d", &pfx, &pfy);
            pf->data[0][0] = pfx;
            pf->data[1][0] = pfy;
            pf->data[2][0] = 1;
            printf("Dame puntos:\n");
          }
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          rotation2dWithPivot(point, pf, result, getRadians(theta));
          break;
        case 5 :
          if (i == 0) {
            printf("Sx, Sy: ");
            scanf("%f %f", &sx, &sy);
            printf("Punto fijo: ");
            scanf("%d %d", &pfx, &pfy);
            pf->data[0][0] = pfx;
            pf->data[1][0] = pfy;
            pf->data[2][0] = 1;
            printf("Dame puntos:\n");
          }
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          scale2dFixedPoint(point, pf, result, sx, sy);
          break;
        case 6 :
          if (i == 0)
            printf("Dame puntos:\n");
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          reflectionX2d(point, result);
          break;
        case 7 :
          if (i == 0)
            printf("Dame puntos:\n");
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          reflectionY2d(point, result);
          break;
        case 8 :
          if (i == 0)
            printf("Dame puntos:\n");
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          reflectionXY2d(point, result);
          break;
        case 9 :
          if (i == 0)
            printf("Dame puntos:\n");
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          reflectionYeX2d(point, result);
          break;
        case 10:
          if (i == 0) {
            printf("Punto fijo: ");
            scanf("%d %d", &pfx, &pfy);
            pf->data[0][0] = pfx;
            pf->data[1][0] = pfy;
            pf->data[2][0] = 1;
            printf("Dame puntos:\n");
          }
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          rotation2dWithPivot(point, pf, result, getRadians(180.0f));
          break;
        case 11:
          if (i == 0)
            printf("Dame puntos:\n");
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          reflectionYmX2d(point, result);
          break;
        case 12:
          if (i == 0) {
            printf("m: ");
            scanf("%f", &m);
            printf("b: ");
            scanf("%f", &b);
            printf("Dame puntos:\n");
          }
          scanf("%d %d", &x, &y);
          point->data[0][0] = x;
          point->data[1][0] = y;
          point->data[2][0] = 1;
          reflectionGeneral2d(point, result, m, b);
          break;
        default:  
          break;
      }
      printf("(%d,%d)\n", (int)roundf(result->data[0][0]),
                          (int)roundf(result->data[1][0]));
    }
    
    printf("\n[Enter] para continuar...");
    while (getchar() != '\n')
      ;
    while (getchar() != '\n')
      ;
    
    system("cls");
    system("clear");
  }
  

  return EXIT_SUCCESS;
}
