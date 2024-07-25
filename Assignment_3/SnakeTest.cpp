// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Snake.h"
#include <gtest/gtest.h>
#include <ncurses.h>

TEST(Snake, moveBox) {
  row = 10;
  col = 20;
  moveBox(KEY_UP);
  ASSERT_EQ(row, 9);
  ASSERT_EQ(col, 20);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}