// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once
#include "TerminalManager.h"
#include <ncurses.h>

//______________________________________________________________________________
TerminalManager::TerminalManager() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);

  start_color();
  // Initialize one color pair for each color.
  // For simplicity reasons we only use the foreground
  // colors.
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);

  // COLS and LINES are global variables from ncurses (dimensions of screen).
  setKScreenWidth(COLS / 2);
  setKScreenHeight(LINES);
  UserInput userInput;
}

//______________________________________________________________________________
TerminalManager::~TerminalManager() { endwin(); }

//____________________________________________________________________________________
void TerminalManager::refreshScreen() { refresh(); }

//____________________________________________________________________________________
void TerminalManager::clearScreen() { clear(); }

//____________________________________________________________________________________
void TerminalManager::displayText(int row, int col, const char *text) {
  mvprintw(row, col, text);
}

//____________________________________________________________________________________
void TerminalManager::drawCell(int row, int col, bool alive) {
  if (alive) {
    attron(COLOR_PAIR(1));
  } else {
    attron(COLOR_PAIR(3));
  }
  mvprintw(row, col, "  ");
  if (alive) {
    attroff(COLOR_PAIR(1));
  } else {
    attroff(COLOR_PAIR(3));
  }
}

//______________________________________________________________________________

UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keyCode_ = getch();
  return userInput;
}

//____________________________________________________________________________________
bool UserInput::isEscape() { return keyCode_ == 27; }

//____________________________________________________________________________________
bool UserInput::isSpace() { return keyCode_ == ' '; }

//____________________________________________________________________________________
bool UserInput::isR() { return keyCode_ == 'r'; }

//____________________________________________________________________________________
bool UserInput::isS() { return keyCode_ == 's'; }