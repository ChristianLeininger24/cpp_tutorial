// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once

#include "TerminalManager.h"
class GameOfLife {
private:
  // The maximal number of cells, and the actual number of cells that is used by
  // the game.
  static const int MAX_NUM_CELLS = 1'000'000;

  bool grid1_[MAX_NUM_CELLS] = {};
  bool grid2_[MAX_NUM_CELLS] = {};
  // The two pointers to the current and previous grid, they are switched after
  // each iteration.
  bool *previousGrid_ = grid1_;
  bool *currentGrid_ = grid2_;

  // Last coordinate clicked inside grid.
  int lastClickedCol_ = -1;
  int lastClickedRow_ = -1;

  // Additional global state
  bool isRunning_ = false;
  int numSteps_ = 0;
  int numLivingCells_ = 0;

  TerminalManager *terminalManager_ = nullptr;
  // Intializes the terminal.
public:
  // constructor
  GameOfLife(TerminalManager *terminalManager);

  // Initializes the game.
  void run();

  // Initializes the game.
  void initGame();

  // Processes the user input.
  bool handleInput(UserInput userInput);

  // Updates the state of the game.
  void updateState();

  // Shows the state of the game.
  void showState();

  // set value to current grid
  void setCurrent(int row, int col, bool value);

  // set value to previous grid
  void setPrevious(int row, int col, bool value);

  // count the number of living neighbors
  int numAliveNeighbours(int row, int col);

  // check if state is accessible
  bool isLegalPosition(int row, int col);

  // get function for current grid
  bool getCurrent(int row, int col);

  // get function for previous grid
  bool getPrevious(int row, int col);

  // get function for grid
  bool get(int row, int col, bool isPrevious);

  // set function for current grid
  void set(int row, int col, bool value, bool isPrevious);

}; // namespace GameOfLife