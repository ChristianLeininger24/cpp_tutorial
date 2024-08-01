// Copyright 2024
// Author: Christian Leininger <programmer72024@gmail.com>
// Author: Hannah Bast <bast@cs.uni-freiburg.de>

#pragma once



// class for snake
class Snake {
private:
 // save amount of screen pixel in y and x direction
 int kScreenWidth_;
 int kScreenHeight_;

 // save snake position
 int kSnakeX_;
 int kSnakeY_;

 // speed of the snake
 int kSpeedX_;
 int kSpeedY_;

 // play funktion
 

 void initTerminal();

 // Initialize game
 void initGame();

 // draw pixel on screen
 void drawPixel(int x, int y, int color);

 // draw snake
 void drawSnake(int color);

 // draw boarder around screen
 void drawBoarder(int color);

 // move snake
 void moveSnake();

 // check if snake is out of bounds
 bool isOutOfBounds();

 // changes the direction of the snake
 bool handleInput(int key);
public:
 // play the game
 void play();   
};
