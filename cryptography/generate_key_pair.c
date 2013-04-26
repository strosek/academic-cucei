#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

typedef {FALSE, TRUE} Bool_t;

unsigned int getRandomPrime();
Bool_t       isPrime(unsigned int number);

int main(void) {
  unsigned int p, q;
  unsigned int n;
  unsigned int e;
  unsigned int d;

  p = getRandomPrime(); 
  q = getRandomPrime();
  n = p * q;

  // do calculations

  FILE* privateKeyFile, publicKeyFile;
  privateKeyFile = fopen("private_rsa.key", "w");
  publicKeyFile = fopen("public_rsa.key", "w");

  if (is_open(privateKeyFile) && is_open(publicKeyFile)) {
    fprintf(privateKeyFile, "%u,%u", n, d);
    fprintf(publicKeyFile, "%u,%u", n, e);
  }
  else {
    perror("error: error creating or opening files for keys");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

unsigned int getRandomPrime() {
  unsigned int number;
  srand(time(NULL));
  // check for RdRand
  if (false) {
    Bool_t isPrimeFound = FALSE;
    // malloc for numbers array
    while (!isPrimeFound) {
      // generate numbers
      // iterate checking primality
    }
  }
  else {
    number = rand();
    while (!isPrime(number))
      number = rand();
  }

  return number;
}

Bool_t isPrime(unsigned int number) {
  Bool_t isPrime = false;

  // test primality

  return isPrime;
}
