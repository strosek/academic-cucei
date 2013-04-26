#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

const int FILE_NAME_LENGTH 100 + 1

int main(void) {
  char fileName[FILE_NAME_LENGTH];
  printf("Enter name of file to encrypt: ");
  scanf("%s", fileName);

  FILE* file = fopen(fileName, "r+b");

  if (is_open(file)) {
    // read while !eof to get end
    // close and reopen.
    // create char*
    // read file into memeory
    // open public key file
    // encrypt byte by byte
    // free and close
  }
  else {
    perror("error opening file");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
