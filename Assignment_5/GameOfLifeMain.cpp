// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./GameOfLife.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  TerminalManager terminalManager;
  GameOfLife game(&terminalManager);
  game.run();
  return 0;
}
