// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include <cmath>
#include <cstdio>

// compute the greatest common divisor of a and b
// use an iterative version of the Euclidean algorithm
int computeGcd(int num1, int num2, bool verbose = false) {
  int count = 0;
  while (num2 != 0) {
    if (verbose) {
      printf("Step %d: %d %% %d = %d\n", count, num1, num2, num1 % num2);
    }
    int temp = num2;
    num2 = num1 % num2;
    num1 = temp;
    count++;
  }
  if (verbose) {
    printf("gcd is %d\n", num1);
  }
  return num1;
}
