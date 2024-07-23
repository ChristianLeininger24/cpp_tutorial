// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Gcd.cpp"
#include <cstdio>

int main(int argc, char **argv) {
  // check if there are 2 arguments
  if (argc != 3) {
    printf("Usage: %s <number1> <number2>\n", argv[0]);
    return 1;
  }
  int number1 = atoi(argv[1]);
  int number2 = atoi(argv[2]);
  bool verbose = true;
  computeGcd(number1, number2, verbose);
  return 0;
}
