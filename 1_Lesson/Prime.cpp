// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

// funtion to check if a number is prime
#include <cmath>
#include <cstdio>

bool checkIfPrime(int number, bool verbose = false) {
  //  if number is less than or equal to 1, it is not prime
  if (verbose) {
    printf("Checking if %d is prime\n", number);
  }
  if (number <= 1) {
    return false;
  }
  // 2 is the only even prime number
  if (number == 2) {
    return true;
  }
  // simple loop to check if number is divisible by any number other than 1 and
  // itself use the fact that only to the square root of the number needs to be
  // checked
  double root = std::ceil(sqrt(number));
  if (verbose) {
    printf("Root of %d is %f\n", number, root);
  }
  for (int i = 2; i <= root; i++) {
    if (number % i == 0) {
      if (verbose) {
        printf("%d is divisible by %d\n", number, i);
      }
      return false;
    }
  }
  if (verbose) {
    printf("%d is prime\n", number);
  }
  return true;
}