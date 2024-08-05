// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once
#include "TerminalManager.h"
#include <tuple>

class UserInput {
public:
  int keyCode_;
  int mouseRow_;
  int mouseCol_;
  bool isEscape();
  bool isSpace();
  bool isR();
  bool isS();
  bool isMouseClick();
  void updateMousePosition();
};

class TerminalManager {
private:
  int kScreenWidth_;
  int kScreenHeight_;

public:
  TerminalManager();
  ~TerminalManager();
  //______________________________________________________________________________
  void setKScreenWidth(int width) { kScreenWidth_ = width; }
  //______________________________________________________________________________
  void setKScreenHeight(int height) { kScreenHeight_ = height; }
  //______________________________________________________________________________
  int getKScreenWidth() { return kScreenWidth_; }
  //______________________________________________________________________________
  int getKScreenHeight() { return kScreenHeight_; }
  void refreshScreen();
  void displayText(int row, int col, const char *text);
  void drawCell(int row, int col, bool alive);
  void clearScreen();
  UserInput getUserInput();
};
