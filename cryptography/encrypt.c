#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

const int FILE_NAME_LENGTH = 100 + 1;

unsigned int uintpow(unsigned int a, unsigned int b);

int main(void) {
  printf("RSA ENCRYPT PROGRAM\n");
  printf("===================\n\n");
#pragma omp parallel
  printf("Running shared-memory parallelism using [%d] threads!...\n", 
         omp_get_max_threads());
  
  printf("\n\n");

  char fileName[FILE_NAME_LENGTH];
  printf("Enter name of file to encrypt: ");
  scanf("%s", fileName);

  FILE* file = fopen(fileName, "r+b");

  if (file != NULL) {
    size_t fileSize = 0;
    while (fgetc(file) != EOF)
      ++fileSize;
    printf("%lu\n", fileSize);
    
    fclose(file);
    file = fopen(fileName, "r+b");
    if (file != NULL) {
      int* fileBuffer = (int*)malloc(sizeof(char) * fileSize);
      fread(fileBuffer, sizeof(int), fileSize / sizeof(int), file);
      FILE* publicKeyFile = fopen("public_rsa.key", "r");
      unsigned int n, e;
      fscanf(publicKeyFile, "%u %u", &n, &e);
      printf("%u %u", n ,e);

      size_t i;
#pragma omp for
      for (i = 0; i < fileSize / sizeof(int); ++i) {
        printf("%u ", uintpow(fileBuffer[i], e) % n);
        fileBuffer[i] = uintpow(fileBuffer[i], e) % n;
      }

      fclose(file);
      file = fopen(fileName, "w+b");
      
//       fwrite(fileBuffer, sizeof(int), fileSize / sizeof(int), file);
    }
  }
  else {
    perror("rsa_encrypt: error opening file");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

unsigned int uintpow(unsigned int a, unsigned int b) {
  if (a == 0)
    return 0;
  if (b == 0)
    return 1;
    
  unsigned int i;
  unsigned int result = 1;
  for (i = 0; i < b; ++i)
      result *= a;
  
  return result;
}
