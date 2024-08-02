// Copyright 2024
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
// Author: Christian Leininger <programmer72024@gmail.com>

#include "TerminalManager.h"
#include <ncurses.h>

//____________________________________________________________________________________
// gloabal variables
const int TerminalManager::green = COLOR_GREEN;
const int TerminalManager::red = COLOR_RED;
const int TerminalManager::black = COLOR_BLACK;
const int TerminalManager::blue = COLOR_BLUE;
const int TerminalManager::yellow = COLOR_YELLOW;
const int TerminalManager::white = COLOR_WHITE;

//____________________________________________________________________________________
TerminalManager::TerminalManager() {
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
  setKScreenWidth(COLS / 2);
  setKScreenHeight(LINES);
  UserInput userInput;
}

//____________________________________________________________________________________
TerminalManager::~TerminalManager() { endwin(); }

//____________________________________________________________________________________
void TerminalManager::refreshScreen() { refresh(); }

// ____________________________________________________________________________________
void TerminalManager::endDisplay() {
  attron(COLOR_PAIR(6)); // set it to white on black
  mvprintw(getKScreenHeight() / 2, getKScreenWidth() / 2,
           "Game Over! Press 'ESC' to quit.");
}

//____________________________________________________________________________________
void TerminalManager::drawPixel(int x, int y, int color) {
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
UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keyCode_ = getch();
  return userInput;
}

//____________________________________________________________________________________
bool UserInput::isEscape() { return keyCode_ == 27; }

//____________________________________________________________________________________
bool UserInput::isUp() { return keyCode_ == KEY_UP; }

//____________________________________________________________________________________
bool UserInput::isDown() { return keyCode_ == KEY_DOWN; }

//____________________________________________________________________________________
bool UserInput::isLeft() { return keyCode_ == KEY_LEFT; }

//____________________________________________________________________________________
bool UserInput::isRight() { return keyCode_ == KEY_RIGHT; }