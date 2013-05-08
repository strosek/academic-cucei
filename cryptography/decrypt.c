#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

const int FILE_NAME_LENGTH = 100 + 1;


int main(void) {
  char fileName[FILE_NAME_LENGTH];
  printf("DECRYPT PROGRAM\n");
  printf("===============\n\n");

  printf("Running shared-memory parallellism using [%d] threads...", 
         omp_get_max_threads());

  printf("Name of file to decrypt: ");
  scanf("%s", fileName);

  FILE* file = fopen(fileName, "wb");

  return EXIT_SUCCESS;
}

