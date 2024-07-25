// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Snake.h"
#include <ncurses.h>
#include <unistd.h>
#include <random>
// ____________________________________________________________________________
int row;
int col;
int boxRow;
int boxCol;
std::random_device rd;  // Obtain a random number from hardware
std::mt19937 eng(rd()); // Seed the generator
std::uniform_int_distribution<> distr(0, LINES - 1); // Define the range
std::uniform_int_distribution<> distc(0, COLS - 1); // Define the range

// ____________________________________________________________________________
void startNcurses() {
  initscr();
  // Check if initialization was successful
  if (stdscr == NULL) {
    fprintf(stderr, "Error initializing ncurses.\n");
  }
  curs_set(false);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
}

// ____________________________________________________________________________
void endNcurses() { endwin(); }

// ____________________________________________________________________________
void drawBox() {
  attron(COLOR_PAIR(2) | A_REVERSE);
  mvprintw(row, col, "  ");
  attroff(COLOR_PAIR(2) | A_REVERSE);
  refresh();
}

// ____________________________________________________________________________
void removeBox() {
  mvprintw(row, col, "  ");
  refresh();
}

// ____________________________________________________________________________
bool gameOver() {
  bool game_over = false;
  // Check if the box is at the bottom of the screen
  if (row >= LINES) {
    game_over = true;
  }
  // Check if the box is at the top of the screen
  if (row < 0) {
    game_over = true;
  }
  // Check if the box is at the right of the screen
  if (col >= COLS) {
    game_over = true;
  }
  // Check if the box is at the left of the screen
  if (col < 0) {
    game_over = true;
  }
  if (game_over) {
    mvprintw(LINES / 2, COLS / 2 - 5, "Game Over");
    refresh();
    sleep(2);
  }
  return game_over;
}

// ____________________________________________________________________________
void moveBox(int direction) {
  switch (direction) {
  case KEY_UP:
    row--;
    break;
  case KEY_DOWN:
    row++;
    break;
  case KEY_LEFT:
    col--;
    break;
  case KEY_RIGHT:
    col++;
    break;
  }
}

// ____________________________________________________________________________
bool isValidKey(int key){
  return key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT;
}

// ____________________________________________________________________________
void addGoal() {
  boxRow = distr(eng) % LINES;
  boxCol = distc(eng) % COLS;
  attron(COLOR_PAIR(1) | A_REVERSE);
  mvprintw(boxRow, boxCol, "  ");
  attroff(COLOR_PAIR(1) | A_REVERSE);
  refresh();
}