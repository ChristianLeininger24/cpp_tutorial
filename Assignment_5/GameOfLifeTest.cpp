

#include "./GameOfLife.h"
#include <gtest/gtest.h>

TEST(GameOfLife, initGame) {
  initGame();
  EXPECT_EQ(lastClickedRow, -1);
  EXPECT_EQ(lastClickedCol, -1);
}

TEST(GameOfLife, numAliveNeighbours) {
  initGame();

  setCurrent(0, 0, true);
  // should be 0 because it checks the previous grid
  EXPECT_EQ(numAliveNeighbours(0, 0), 0);
  setPrevious(0, 1, true);
  EXPECT_EQ(numAliveNeighbours(0, 0), 1);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}