// Copyright 2024
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
// Author: Christian Leininger <programmer72024@gmail.com>

#include "./Snake.h"
#include <ncurses.h>
#include <unistd.h>

// Speed in pixels per second.
double speed = 1;
// Acceleration in pixel per second squared.
double acceleration = 1;

// Main function.
int main() {
  TerminalManager terminalManager;
  Snake snake(&terminalManager);
  snake.play();
}
