// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./GameOfLife.h"
#include <gtest/gtest.h>



TEST(GameOfLife, setPixel) {
  initGame();
  ASSERT_EQ(getPixel(0, 0), false);
  setPixel(0, 0, true);
  ASSERT_EQ(getPixel(0, 0), true);
  setPixel(0, 0, false);
  ASSERT_EQ(getPixel(0, 0), false);
}

/*
TEST(GameOfLife, aliveNeighbors) {
  int numCols = 5;
  int numRows = 3;
  int maxNumPixels = numCols * numRows;
  initGame();
  int livingCells = aliveNeighbors(0, 0);
  ASSERT_EQ(livingCells, 0);
  setPixel(0, 1, true);
  livingCells = aliveNeighbors(0, 0);
  ASSERT_EQ(livingCells, 1);
}
*/

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}