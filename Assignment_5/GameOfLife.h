

#pragma once

class GameOfLife {
// The maximal number of cells, and the actual number of cells that is used by
// the game.
const int MAX_NUM_CELLS = 1'000'000;
extern int numCols;
extern int numRows;

// The two pointers to the current and previous grid, they are switched after
// each iteration.
extern bool *previousGrid;
extern bool *currentGrid;

// Last coordinate clicked inside grid.
extern int lastClickedCol;
extern int lastClickedRow;

// Additional global state
extern bool isRunning;
extern int numSteps;
extern int numLivingCells;

// Intializes the terminal.
void initTerminal();

// Initializes the game.
void initGame();

// Processes the user input.
bool processUserInput(int key);

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
bool isLealPosition(int row, int col);

// get function for current grid
bool getCurrent(int row, int col);

// get function for previous grid
bool getPrevious(int row, int col);

// get function for grid
bool get(int row, int col, bool isPrevious);

// set function for current grid
void set(int row, int col, bool value, bool isPrevious);

};  // namespace GameOfLife