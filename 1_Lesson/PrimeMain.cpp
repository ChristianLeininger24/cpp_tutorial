// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Prime.cpp"
#include <cstdio>

int main(int argc, char **argv) {
  // check if there are 2 arguments
  if (argc != 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 1;
  }
  int number = atoi(argv[1]);
  bool verbose = true;
  checkIfPrime(number, verbose);
  return 0;
}
