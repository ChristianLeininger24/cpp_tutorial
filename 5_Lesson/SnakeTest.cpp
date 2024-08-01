// Copyright 2024
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
// Author: Christian Leininger <programmer72024@gmail.com>


#include <gtest/gtest.h>
#include <ncurses.h>

#include "./Snake.h"

TEST(Snake, moveSnake) {
  Snake snake;
  snake.initGame();
  EXPECT_EQ(snake.kSnakeX_, 1);
  EXPECT_EQ(snake.kSnakeY_, 0);
  snake.moveSnake();
  EXPECT_EQ(snake.kSnakeX_, 2);
  EXPECT_EQ(snake.kSnakeY_, 0);
}