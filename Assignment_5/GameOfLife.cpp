// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once
#include "./GameOfLife.h"
#include "TerminalManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//______________________________________________________________________________
GameOfLife::GameOfLife(TerminalManager *terminalManager) {
  terminalManager_ = terminalManager;
}

//______________________________________________________________________________
void GameOfLife::initGame() {
  // Initialize the game.
  previousGrid_ = grid1_;
  currentGrid_ = grid2_;
  for (int row = 0; row < (*terminalManager_).getKScreenHeight(); ++row) {
    for (int col = 0; col < (*terminalManager_).getKScreenWidth(); ++col) {
      setCurrent(row, col, false);
      setPrevious(row, col, false);
    }
  }

  lastClickedRow_ = -1;
  lastClickedCol_ = -1;

  isRunning_ = false;
  numSteps_ = 0;
  numLivingCells_ = 0;
}

void GameOfLife::run() {
  initGame();

  // (*terminalManager_).clearScreen();
  while (handleInput((*terminalManager_).getUserInput())) {
    showState();
    if (isRunning_) {
      updateState();
      usleep(100'000);
    }
  }
}

// ____________________________________________________________________________
void GameOfLife::showState() {

  for (int row = 0; row < (*terminalManager_).getKScreenHeight(); ++row) {
    for (int col = 0; col < (*terminalManager_).getKScreenWidth(); ++col) {
      bool isAlive = getCurrent(row, col);
      (*terminalManager_).drawCell(row, col * 2, isAlive);
    }
  }
  const int bufSize = 100;
  char buffer[bufSize];
  snprintf(buffer, bufSize, "Step: %9d Cells alive: %4d Running: %d", numSteps_,
           numLivingCells_, isRunning_);
  (*terminalManager_).displayText(0, 0, buffer);
  (*terminalManager_).refreshScreen();
}

// ____________________________________________________________________________
bool GameOfLife::handleInput(UserInput userInput) {
  if (userInput.isEscape()) {
    // Exit the game.
    return false;
  } else if (userInput.isSpace()) {
    isRunning_ = !isRunning_;
  } else if (userInput.isR()) {
    // genrate random pixels
    for (int row = 0; row < (*terminalManager_).getKScreenHeight(); ++row) {
      for (int col = 0; col < (*terminalManager_).getKScreenWidth(); ++col) {
        setCurrent(row, col, drand48() > 0.8);
      }
    }
  } else if (userInput.isS()) {
    // Step update the screen
    updateState();
  }
  if (userInput.isMouseClick()) {
    userInput.updateMousePosition();
    lastClickedCol_ = userInput.mouseCol_;
    lastClickedRow_ = userInput.mouseRow_;
    bool prev = getCurrent(lastClickedRow_, lastClickedCol_);
    setCurrent(lastClickedRow_, lastClickedCol_, !prev);
  }
  return true;
}

//______________________________________________________________________________
void GameOfLife::updateState() {
  numSteps_++;
  numLivingCells_ = 0;
  // Swap the grids.
  bool *temp = previousGrid_;
  previousGrid_ = currentGrid_;
  currentGrid_ = temp;
  for (int row = 0; row < (*terminalManager_).getKScreenHeight(); ++row) {
    for (int col = 0; col < (*terminalManager_).getKScreenWidth(); ++col) {
      int numAlive = numAliveNeighbours(row, col);
      bool isAlive = getCurrent(row, col);
      if (isAlive) {
        numLivingCells_++;
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
int GameOfLife::numAliveNeighbours(int row, int col) {
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

/*
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







*/
// __________________________________________________________________________
bool GameOfLife::isLegalPosition(int row, int col) {
  return (row >= 0) && (col >= 0) &&
         (row < (*terminalManager_).getKScreenHeight()) &&
         (col < (*terminalManager_).getKScreenWidth());
}

// __________________________________________________________________________
bool GameOfLife::get(int row, int col, bool isPrevious) {
  // return false for out-of-bounds access.
  if (!isLegalPosition(row, col)) {
    return false;
  }
  int idx = row * (*terminalManager_).getKScreenWidth() + col;
  bool *grid = isPrevious ? previousGrid_ : currentGrid_;
  return grid[idx];
}

// __________________________________________________________________________
void GameOfLife::set(int row, int col, bool value, bool isPrevious) {
  // do nothing for out of bounds acces.
  if (!isLegalPosition(row, col)) {
    return;
  }
  int idx = row * (*terminalManager_).getKScreenWidth() + col;
  bool *grid = isPrevious ? previousGrid_ : currentGrid_;
  grid[idx] = value;
}

// ____________________________________________________________________________
void GameOfLife::setPrevious(int row, int col, bool value) {
  set(row, col, value, true);
}
void GameOfLife::setCurrent(int row, int col, bool value) {
  set(row, col, value, false);
}
bool GameOfLife::getPrevious(int row, int col) { return get(row, col, true); }
bool GameOfLife::getCurrent(int row, int col) { return get(row, col, false); }