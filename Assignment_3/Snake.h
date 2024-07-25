// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once

// Position of the box.
extern int row;
extern int col;

// position of the box
extern int boxRow;
extern int boxCol;

// count points
extern int points;


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

// check if key is Up, Down, Left, Right
bool isValidKey(int key);

// add a goal
void addGoal();

// draw points 
void drawPoints();

// Clean up Ncurses.
void endNcurses();
