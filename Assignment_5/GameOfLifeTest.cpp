

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

TEST(GameOfLife, processUserInputQuit) { ASSERT_FALSE(processUserInput('q')); }

TEST(GameOfLife, processUserInputSpace) {
  isRunning = false;
  ASSERT_TRUE(processUserInput(' '));
  ASSERT_TRUE(isRunning);
  ASSERT_TRUE(processUserInput(' '));
  ASSERT_FALSE(isRunning);
}

TEST(GameOfLife, processUserInputSmallS) {
  initGame();
  numSteps = 0;
  ASSERT_TRUE(processUserInput('s'));
  ASSERT_EQ(numSteps, 1);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}