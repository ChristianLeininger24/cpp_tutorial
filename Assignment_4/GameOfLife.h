// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once

#include <ncurses.h>
#include <string>

// Position of the box.
extern int row;
extern int col;
extern int numCols;
extern int numRows;

// position of the box
extern int boxRow;
extern int boxCol;

// state of all pixels
const int MAX_NUM_PIXELS = 100000;
extern bool pixels[MAX_NUM_PIXELS];

extern std::string state;

// Draw a box.
void drawBox();

// Initialize the game.
void initGame();

// set a pixel of the screen
void setPixel(int row, int col, bool value);

// get a pixel state of the screen
bool getPixel(int row, int col);

// count the living cells
int countLivingCells();

// init Terminal
void initTerminal();

// draw all pixels
void drawPixels();

// set random pixels
void setRandomPixels();

// prozess user input
bool processUserInput(int key);

// get probability
bool setBoolWithProbability(double probability);

// Clean up Ncurses.
void endNcurses();
