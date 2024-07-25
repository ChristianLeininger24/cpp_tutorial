// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once

// Position of the box.
extern int row;
extern int col;

// Initialize Ncurses.
void startNcurses();

// Draw a box.
void drawBox();

// Remove a box.
void removeBox();

// Check if the game is over.
bool gameOver();

// move the box
void moveBox(int key);

// Clean up Ncurses.
void endNcurses();
