#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

const int FILE_NAME_LENGTH = 100 + 1;

unsigned int uintpow(unsigned int a, unsigned int b);

int main(void) {
  printf("RSA DECRYPT PROGRAM\n");
  printf("===================\n\n");
#pragma omp parallel
  printf("Running shared-memory parallelism using [%d] threads!...\n", 
         omp_get_max_threads());
  
  printf("\n\n");

  char fileName[FILE_NAME_LENGTH];
  printf("Enter name of file to decrypt: ");
  scanf("%s", fileName);

  FILE* file = fopen(fileName, "r+b");

  if (file != NULL) {
    size_t fileSize = 0;
    while (fgetc(file) != EOF)
      ++fileSize;
    printf("%lu\n", fileSize);
    
    fclose(file);
    file = fopen(fileName, "r+");
    if (file != NULL) {
      char* fileBuffer = (char*)malloc(sizeof(char) * fileSize);
      fread(fileBuffer, sizeof(char), fileSize / sizeof(char), file);
      FILE* privateKeyFile = fopen("private_rsa.key", "r");
      unsigned int n, d;
      fscanf(privateKeyFile, "%u %u", &n, &d);
      printf("%u %u\n", n ,d);

      size_t i;
#pragma omp for
      for (i = 0; i < fileSize / sizeof(char); ++i) {
        printf("original value %c \n", (char)fileBuffer[i]);
        printf("%u \n", (char)(uintpow(fileBuffer[i], d) % n));
        fileBuffer[i] = (char)(uintpow(fileBuffer[i], d) % n);
      }

      fclose(file);
      file = fopen(fileName, "w");
      
      fwrite(fileBuffer, sizeof(char), fileSize / sizeof(char), file);
    }
  }
  else {
    perror("rsa_decrypt: error opening file");
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
