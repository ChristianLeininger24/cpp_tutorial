

#include "./GameOfLife.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  // Initialize terminal and grid.
  printf("Start Game of Life\n");
  printf("Before initTerminal\n");
  printf("previousGrid: %p\n", previousGrid);
  printf("currentGrid: %p\n", currentGrid);
  printf("numCols: %d\n", numCols);
  printf("numRows: %d\n", numRows);
  printf("MAX_NUM_CELLS: %d\n", MAX_NUM_CELLS);
  printf("is Running: %d\n", isRunning);
  printf("numSteps: %d\n", numSteps);
  printf("last clicked row: %d\n", lastClickedRow);
  initTerminal();
  initGame();

  setCurrent(numRows / 2, numCols / 2, true);
  setCurrent(numRows / 2, numCols / 2 + 1, true);
  setCurrent(numRows / 2, numCols / 2 - 1, true);
  setCurrent(numRows / 2 + 1, numCols / 2, true);
  setCurrent(numRows / 2 - 1, numCols / 2, true);
  setCurrent(numRows / 2 + 1, numCols / 2 + 1, true);
  while (processUserInput(getch())) {
    if (isRunning) {
      updateState();
    }
    // Draw and wait.
    showState();
    refresh();
    usleep(1000 * 100);
  }
  endwin();
  printf("After initTerminal\n");
  printf("previousGrid: %p\n", previousGrid);
  printf("currentGrid: %p\n", currentGrid);

  printf("switching grids\n");
  bool *temp = previousGrid;
  previousGrid = currentGrid;
  currentGrid = temp;
  printf("previousGrid: %p\n", previousGrid);
  printf("currentGrid: %p\n", currentGrid);
  printf("last clicked row: %d\n", lastClickedRow);
  if (numRows * numCols > MAX_NUM_CELLS) {
    printf("Screen too large, increase MAX_NUM_PIXELS\n");
    return 1;
  }
  // Clean up window.
}
/*
  while (processUserInput(getch())) {
    if (isRunning) {
      updateState();
    }
    // Draw and wait.
    showState();
    usleep(50 * 1000);
  }
  // Clean up window.
  endwin();
}
*/