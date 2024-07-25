// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Snake.h"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char **argv) {
  printf("Start Snake\n");
  startNcurses();
  // Initialize ncurses

  row = LINES / 2;
  col = COLS / 2;
  std::cout << "LINES " << row << std::endl;
  std::cout << "COLS " << col << std::endl;
  int key = KEY_DOWN;
  int direction = KEY_DOWN;

  while (true) {
    drawBox();
    usleep(1000 * 100);
    removeBox();
    key = getch();
    if (key != ERR) {
      direction = key;
    }
    moveBox(direction); //
    if (gameOver()) {
      break;
    }
  }

  //
  // Wait for 5 seco

  endNcurses();
  return 0;
}
