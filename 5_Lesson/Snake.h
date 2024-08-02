// Copyright 2024
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once
#include "./TerminalManager.h"
#include <gtest/gtest.h>

// class for snake
class Snake {
private:
  // save snake position
  int kSnakeX_;
  int kSnakeY_;

  // speed of the snake
  int kSpeedX_;
  int kSpeedY_;

  TerminalManager *terminalManager_;
  void initTerminal();

  // Initialize game
  void initGame();

  // draw snake
  void drawSnake(int color);

  // draw boarder around screen
  void drawBoarder(int color);

  // move snake
  void moveSnake();
  FRIEND_TEST(Snake, moveSnake);

  // check if snake is out of bounds
  bool isOutOfBounds();

  // changes the direction of the snake
  void handleInput(UserInput userInput);

public:
  // constructor
  Snake(TerminalManager *terminalManager);
  // play the game
  void play();
};
