// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./GameOfLife.h"
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
// ____________________________________________________________________________
int row;
int col;
int numCols = 10;  // use 10 for testing
int numRows = 10; // use 10 for testing
int livingCells;
int maxNumPixels;

bool current_pixels[MAX_NUM_PIXELS];
bool new_pixels[MAX_NUM_PIXELS];

std::string state = "default";

int numSteps;

// ____________________________________________________________________________
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  numCols = COLS / 2;
  numRows = LINES;
}

//____________________________________________________________________________
void initGame() {
  // state of the game hold or run
  state = "hold";
  maxNumPixels = numCols * numRows;
  // set all pixels to false
  for (int i = 0; i < maxNumPixels; i++) {
    current_pixels[i] = false;
    new_pixels[i] = false;
  }
  livingCells = 0;
  numSteps = 0;
}

// ____________________________________________________________________________
void setPixel(int row, int col, bool value) {
  // convert 2D to 1D
  current_pixels[row * numCols + col] = value;
}

// ____________________________________________________________________________
bool getPixel(int row, int col) { 
  int pos = row * numCols + col;
  // check befor the array is not out of bounds
  if (pos < 0 || pos >= maxNumPixels) {
    return false;
  }
  return current_pixels[pos]; }

// ____________________________________________________________________________
void drawPixels() {
  attron(COLOR_PAIR(2));
  for (int i = 3; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (getPixel(i, j)) {
        attron(A_REVERSE);
      }
      mvprintw(i, j * 2, "  ");
      if (getPixel(i, j)) {
        attroff(A_REVERSE);
      }
    }
  }
  attroff(COLOR_PAIR(2));
}

// ____________________________________________________________________________
void setRandomPixels() {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      setPixel(i, j, setBoolWithProbability(0.2));
    }
  }
}
// ____________________________________________________________________________
bool setBoolWithProbability(double probability) {
  // Generate a random number between 0 and RAND_MAX
  int randValue = rand();

  // Normalize the random value to a range of 0 to 1
  double normalizedValue = (double)randValue / RAND_MAX;

  // Check if the normalized value is less than the given probability
  return normalizedValue < probability;
}

// ____________________________________________________________________________
int countLivingCells() {
  int count = 0;
  int col = 0;
  int row = 0;
  for (int i = 0; i < maxNumPixels; i++) {
    row = i % numCols;
    col = i / numCols;
    if (getPixel(row, col)) {
      count++;
    }
  }
  return count;
}

// ____________________________________________________________________________
bool processUserInput(int key) {
  bool quite = false;
  switch (key) {
  case 'q':
    quite = true;
    break;
  case 'r':
    setRandomPixels();
    break;
  case ' ':
    clear();
    if (state == "hold") {
      state = "run";
    } else {
      state = "hold";
    }
    break;
  }

  return quite;
}

// ____________________________________________________________________________
void updateState() {
  mvprintw(1, 0, " steps taken %d  current state is : %s", numSteps,  state.c_str());
  if (state == "run") {
    numSteps++;
    copyArray();
  }
}

// ____________________________________________________________________________
void copyArray() {
  for (int i = 0; i < maxNumPixels; i++) {
    createNewState();
    current_pixels[i] = new_pixels[i];
  }
}

// ____________________________________________________________________________
void createNewState() {
  int livingNeighbors = 0;
  for (int i = 0; i < maxNumPixels; i++) {
    int row = i % numCols;
    int col = i / numCols;
    livingNeighbors = aliveNeighbors(row, col);
    if (getPixel(row, col)) {
      if (livingNeighbors < 2 || livingNeighbors > 3) {
        new_pixels[i] = false;
      } else {
        new_pixels[i] = true;
      }
    } else {
      if (livingNeighbors == 3) {
        new_pixels[i] = true;
      } else {
        new_pixels[i] = false;
      }
    }
  }
}

// ____________________________________________________________________________
int aliveNeighbors(int row, int col) {
  int count = 0;
  int x;
  int y;
  // loop over all possible 8 neighbours
  // -1 -1 | -1 0 | -1 1
  // 0 -1  | current cell | 0 1
  // 1 -1  | 1 0  | 1 1
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i == 0 && j == 0) {
        // skip the current cell
        continue;
      }
      x = row + i;
      y = col + j;
      if (getPixel(x, y)) {
        count++;
      }
    }
  }
  return count;
}
