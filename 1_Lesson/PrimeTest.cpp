// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Prime.cpp"
#include <gtest/gtest.h>

TEST(Prime, checkIfPrime) { ASSERT_EQ(checkIfPrime(1), false); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
