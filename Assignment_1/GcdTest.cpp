// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Gcd.cpp"
#include <gtest/gtest.h>

TEST(Gcd, ComputeGcd) { ASSERT_EQ(computeGcd(132, 28), 4); 
  ASSERT_EQ(computeGcd(56, 28), 28);
  ASSERT_EQ(computeGcd(56, 0), 56);
  ASSERT_EQ(computeGcd(112, 56), 56);
  ASSERT_EQ(computeGcd(10, 2), 2);
  ASSERT_EQ(computeGcd(10, 5), 5);
  ASSERT_EQ(computeGcd(10, 3), 1);
  ASSERT_EQ(computeGcd(20, 15), 5);
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
