// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,

#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>

// global variables
int kScreenWidth;
int kScreenHeight;

int kSnakeX;
int kSnakeY;

int kSpeedX;
int kSpeedY;

//____________________________________________________________________________________
void Snake::initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);

  start_color();
  // Initialize one color pair for each color.
  // For simplicity reasons we only use the foreground
  // colors.
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);

  // COLS and LINES are global variables from ncurses (dimensions of screen).
  kScreenWidth_ = COLS / 2;
  kScreenHeight_ = LINES;
}

//____________________________________________________________________________________
void Snake::initGame() {
  // set snake in the middle of the screen
  kSnakeX_ = kScreenWidth_ / 2;
  kSnakeY_ = kScreenHeight_ / 2;
  // Snake moves to the right at the beginning.
  kSpeedX_ = 1;
  kSpeedY_ = 0;
}
//____________________________________________________________________________________
void Snake::drawPixel(int x, int y, int color) {
  int colorPairNum = 1;
  if (color == COLOR_RED) {
    colorPairNum = 2;
  } else if (color == COLOR_BLACK) {
    colorPairNum = 3;
  } else if (color == COLOR_BLUE) {
    colorPairNum = 4;
  } else if (color == COLOR_YELLOW) {
    colorPairNum = 5;
  }
  attron(COLOR_PAIR(colorPairNum));
  for (int j = 0; j < 2; j++) {
    mvprintw(y, x * 2 + j, " ");
  }
}

//____________________________________________________________________________________
void Snake::drawBoarder(int color) {
  // draw first and last row (top and bottom)
  for (int i = 0; i < kScreenWidth_; i++) {
    drawPixel(i, 0, color);
    drawPixel(i, kScreenHeight_ - 1, color);
  }
  // draw first and last column (left and right)
  for (int i = 0; i < kScreenHeight_; i++) {
    drawPixel(0, i, color);
    drawPixel(kScreenWidth_ - 1, i, color);
  }
}

//____________________________________________________________________________________
void Snake::drawSnake(int color) {
  drawPixel(kSnakeX_, kSnakeY_, color);
}
//____________________________________________________________________________________
void Snake::moveSnake() {
  kSnakeX_ += kSpeedX_;
  kSnakeY_ += kSpeedY_;
}

//____________________________________________________________________________________
bool Snake::isOutOfBounds() {
  if (kSnakeX_ <= 0 || kSnakeX_ >= kScreenWidth_ - 1 || kSnakeY_ <= 0 || kSnakeY_ >= kScreenHeight_ - 1) {
    return true;
  }
  return false;
}
// ____________________________________________________________________________________
bool Snake::handleInput(int key) {
  int oldVx = kSpeedX_;
  int oldVy = kSnakeY_;
  // print 
  switch (key) {
  case 27: // ESC
    return true;
  case KEY_DOWN:
    kSpeedX_= 0;
    kSpeedY_ = 1;
    break;
  case KEY_UP:
    kSpeedX_ = 0;
    kSpeedY_ = -1;
    break;
  case KEY_LEFT:
    kSpeedX_ = -1;
    kSpeedY_ = 0;
    break;
  case KEY_RIGHT:
    kSpeedX_ = 1;
    kSpeedY_ = 0;
    break;
  default:
    break;
  }
  // Ignore the change of direction if it is illegal
  if (oldVx + kSpeedX_== 0 && oldVy +  kSpeedY_ == 0) {
    kSpeedX_ = oldVx;
    kSpeedY_ = oldVy;
  }

  return false;
}

//____________________________________________________________________________________
void Snake::play() {
  initTerminal();
  initGame();
  drawBoarder(COLOR_YELLOW);
  while (true) {
    usleep(100000);
    drawSnake(COLOR_BLACK);
    moveSnake();
    drawSnake(COLOR_RED);
    refresh();
    if (isOutOfBounds() || handleInput(getch())) {
      break;
    }

    
  }
  // clear screen
  clear();
  while (true) {
    int key = getch();
    if (key == 'q') {
      break;
    }
    // print on middle of screen
    attron(COLOR_PAIR(6)); // set it to white on black
    mvprintw(kScreenHeight_ / 2, kScreenWidth_ / 2 , "Game Over! Press 'q' to quit.");
  }
  
  endwin();
 
}