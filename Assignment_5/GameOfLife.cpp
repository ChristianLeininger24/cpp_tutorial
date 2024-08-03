

#include "./GameOfLife.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool grid1[MAX_NUM_CELLS];
bool grid2[MAX_NUM_CELLS];
bool *previousGrid;
bool *currentGrid;

// Last click, used to generate glider.
int lastClickedRow;
int lastClickedCol;

// Global state
bool isRunning;
int numSteps;
int numLivingCells;

// set for testing
int numCols = 100;
int numRows = 100;

//______________________________________________________________________________
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);
  keypad(stdscr, TRUE);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  numCols = COLS / 2;
  numRows = LINES;
}

// ____________________________________________________________________________
void initGame() {
  previousGrid = grid1;
  currentGrid = grid2;
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      setCurrent(row, col, false);
      setPrevious(row, col, false);
    }
  }

  lastClickedRow = -1;
  lastClickedCol = -1;

  isRunning = false;
  numSteps = 0;
  numLivingCells = 0;
}

// ____________________________________________________________________________
void showState() {
  // Only draw visible cells.
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      attroff(A_REVERSE);
      if (getCurrent(row, col)) {
        attron(A_REVERSE);
      }
      mvprintw(row, col * 2, "  ");
    }
  }
  attroff(A_REVERSE);
  mvprintw(
      0, 0,
      "Step: %9d Cells alive: %4d Running: %d Mouse click at row %d  call %d ",
      numSteps, numLivingCells, isRunning, lastClickedRow, lastClickedCol);
}

// ____________________________________________________________________________
bool processUserInput(int keycode) {
  MEVENT event;
  switch (keycode) {
  case 'q':
    // Exit
    return false;
  case ' ':
    // Toggle run
    isRunning = !isRunning;
    break;
  case 'c':
    // Clear the grid
    for (int row = 0; row < numRows; ++row) {
      for (int col = 0; col < numCols; ++col) {
        setCurrent(row, col, false);
      }
    }
    break;
  case 'r':
    // Fill randomly
    for (int row = 0; row < numRows; ++row) {
      for (int col = 0; col < numCols; ++col) {
        setCurrent(row, col, drand48() > 0.8);
      }
    }
    break;
  case 's':
    // Step update the screen
    updateState();
    break;

  case KEY_MOUSE:
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        // Store position of click and invert cell.
        // Check if the click was inside the grid:
        //
        lastClickedCol = event.x / 2;
        lastClickedRow = event.y;
        bool prev = getCurrent(lastClickedRow, lastClickedCol);
        setCurrent(lastClickedRow, lastClickedCol, !prev);
      }
    }
    break;
  }
  return true;
}

//______________________________________________________________________________
void updateState() {
  numSteps++;
  numLivingCells = 0;
  // Swap the grids.
  bool *temp = previousGrid;
  previousGrid = currentGrid;
  currentGrid = temp;
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      int numAlive = numAliveNeighbours(row, col);
      bool isAlive = getCurrent(row, col);
      if (isAlive) {
        numLivingCells++;
      }
      // Apply the rules of the game.
      if (isAlive && (numAlive < 2 || numAlive > 3)) {
        setCurrent(row, col, false);
      } else if (!isAlive && numAlive == 3) {
        setCurrent(row, col, true);
      }
    }
  }
}

// ____________________________________________________________________________
int numAliveNeighbours(int row, int col) {
  int result = 0;
  // Check the 3x3 around the given cell.
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      // Ignore the given cell itself
      if (dr == 0 && dc == 0) {
        continue;
      }
      result += getPrevious(row + dr, col + dc);
    }
  }
  return result;
}

// __________________________________________________________________________
bool isLegalPosition(int row, int col) {
  return (row >= 0) && (col >= 0) && (row < numRows) && (col < numCols);
}

// __________________________________________________________________________
bool get(int row, int col, bool isPrevious) {
  // return false for out-of-bounds access.
  if (!isLegalPosition(row, col)) {
    return false;
  }
  int idx = row * numCols + col;
  bool *grid = isPrevious ? previousGrid : currentGrid;
  return grid[idx];
}

// __________________________________________________________________________
void set(int row, int col, bool value, bool isPrevious) {
  // do nothing for out of bounds acces.
  if (!isLegalPosition(row, col)) {
    return;
  }
  int idx = row * numCols + col;
  bool *grid = isPrevious ? previousGrid : currentGrid;
  grid[idx] = value;
}

// ____________________________________________________________________________
void setPrevious(int row, int col, bool value) { set(row, col, value, true); }

// ____________________________________________________________________________
void setCurrent(int row, int col, bool value) { set(row, col, value, false); }

// ____________________________________________________________________________
bool getPrevious(int row, int col) { return get(row, col, true); }

// ____________________________________________________________________________
bool getCurrent(int row, int col) { return get(row, col, false); }