#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

extern int snakeLength;
extern int snakeX[SNAKE_MAX_LENGTH];
extern int snakeY[SNAKE_MAX_LENGTH];
extern int dx, dy;
extern bool gameOver;
extern bool gameWin;
extern int foodX, foodY;
extern int currentToneFrequency;

void handleInput();
void moveSnake();
void checkCollision();
void checkFoodCollision();
void generateFood();
void drawFood();
void drawGame();
void showGameOver();
void showYouWin();
void resetGame();

#endif
