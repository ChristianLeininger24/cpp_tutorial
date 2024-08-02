// Copyright 2024
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
// Author: Christian Leininger <programmer72024@gmail.com>

#include "Snake.h"
#include "TerminalManager.h"
#include <unistd.h>

//____________________________________________________________________________________
Snake::Snake(TerminalManager *terminalManager) {
  terminalManager_ = terminalManager;
}

//____________________________________________________________________________________
void Snake::initGame() {
  // set snake in the middle of the screen
  kSnakeX_ = (*terminalManager_).getKScreenWidth() / 2;
  kSnakeY_ = (*terminalManager_).getKScreenHeight() / 2;
  // Snake moves to the right at the beginning.
  kSpeedX_ = 1;
  kSpeedY_ = 0;
}

//____________________________________________________________________________________
void Snake::drawBoarder(int color) {
  // draw first and last row (top and bottom)
  for (int i = 0; i < (*terminalManager_).getKScreenWidth(); i++) {
    (*terminalManager_).drawPixel(i, 0, color);
    (*terminalManager_)
        .drawPixel(i, (*terminalManager_).getKScreenHeight() - 1, color);
  }
  // draw first and last column (left and right)
  for (int i = 0; i < (*terminalManager_).getKScreenHeight(); i++) {
    (*terminalManager_).drawPixel(0, i, color);
    (*terminalManager_)
        .drawPixel((*terminalManager_).getKScreenWidth() - 1, i, color);
  }
}

//____________________________________________________________________________________
void Snake::drawSnake(int color) {
  (*terminalManager_).drawPixel(kSnakeX_, kSnakeY_, color);
}
//____________________________________________________________________________________
void Snake::moveSnake() {
  kSnakeX_ += kSpeedX_;
  kSnakeY_ += kSpeedY_;
}

//____________________________________________________________________________________
bool Snake::isOutOfBounds() {
  if (kSnakeX_ <= 0 || kSnakeX_ >= (*terminalManager_).getKScreenWidth() - 1 ||
      kSnakeY_ <= 0 || kSnakeY_ >= (*terminalManager_).getKScreenHeight() - 1) {
    return true;
  }
  return false;
}
// ____________________________________________________________________________________
void Snake::handleInput(UserInput userInput) {
  if (userInput.isUp()) {
    kSpeedX_ = 0;
    kSpeedY_ = -1;
  } else if (userInput.isDown()) {
    kSpeedX_ = 0;
    kSpeedY_ = 1;
  } else if (userInput.isLeft()) {
    kSpeedX_ = -1;
    kSpeedY_ = 0;
  } else if (userInput.isRight()) {
    kSpeedX_ = 1;
    kSpeedY_ = 0;
  }
}

//____________________________________________________________________________________
void Snake::play() {
  initGame();
  drawBoarder(TerminalManager::yellow);

  while (true) {
    UserInput userInput = (*terminalManager_).getUserInput();
    handleInput(userInput);
    usleep(100000);
    drawSnake(TerminalManager::black);
    moveSnake();
    drawSnake(TerminalManager::red);
    (*terminalManager_).refreshScreen();
    if (isOutOfBounds() || userInput.isEscape()) {
      break;
    }
  }
  // clear screen
  while (true) {
    UserInput userInput = (*terminalManager_).getUserInput();
    if (userInput.isEscape()) {
      break;
    }
    // print on middle of screen
    (*terminalManager_).endDisplay();
  }
}