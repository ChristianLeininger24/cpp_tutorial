// Copyright 2024
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
// Author: Christian Leininger <programmer72024@gmail.com>

#pragma once
#include "TerminalManager.h"
#include <gtest/gtest.h>

class UserInput {
public:
  int keyCode_;
  bool isEscape();
  bool isUp();
  bool isDown();
  bool isLeft();
  bool isRight();
};

class TerminalManager {
private:
  int kScreenWidth_;
  int kScreenHeight_;

public:
  static const int green;
  static const int red;
  static const int black;
  static const int blue;
  static const int yellow;
  static const int white;

  int getKScreenWidth() { return kScreenWidth_; };
  int getKScreenHeight() { return kScreenHeight_; };
  void setKScreenHeight(int height) { kScreenHeight_ = height; };
  void setKScreenWidth(int width) { kScreenWidth_ = width; };
  // konstruktor
  TerminalManager();
  // destruktor;
  ~TerminalManager();
  // draw pixel on screen
  void drawPixel(int x, int y, int color);
  // refresh screen
  void refreshScreen();
  // end display
  void endDisplay();

  // get user input
  UserInput getUserInput();
};