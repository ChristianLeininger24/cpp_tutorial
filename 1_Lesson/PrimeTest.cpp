// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Prime.cpp"
#include <gtest/gtest.h>

TEST(Prime, checkIfPrime) {
  ASSERT_EQ(checkIfPrime(1), false);
  ASSERT_EQ(checkIfPrime(2), true);
  ASSERT_EQ(checkIfPrime(3), true);
  ASSERT_EQ(checkIfPrime(4), false);
  ASSERT_EQ(checkIfPrime(5), true);
  ASSERT_EQ(checkIfPrime(7), true);
  ASSERT_EQ(checkIfPrime(9), false);
  ASSERT_EQ(checkIfPrime(42), false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
