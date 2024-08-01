
#include "./Snake.h"
#include <ncurses.h>
#include <unistd.h>

// Speed in pixels per second.
double speed = 1;
// Acceleration in pixel per second squared.
double acceleration = 1;

// Main function.
int main() {
  Snake snake;
  snake.play();
}

