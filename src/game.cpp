#include "game.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "constants.h"
#include "menu.h"

extern Adafruit_SSD1306 display;

int snakeLength = 5;
int snakeX[SNAKE_MAX_LENGTH];
int snakeY[SNAKE_MAX_LENGTH];
int dx = SNAKE_BLOCK_SIZE;
int dy = 0;
bool gameOver = false;
bool gameWin = false;
int foodX = -1;
int foodY = -1;
int currentToneFrequency = 600; 


void handleInput() {
  int xValue = analogRead(JOY_HORZ);
  int yValue = analogRead(JOY_VER);
  int threshold = 50;  

  if (xValue < 512 - threshold) {  
    dx = -SNAKE_BLOCK_SIZE;
    dy = 0;
  } else if (xValue > 512 + threshold) {  
    dx = SNAKE_BLOCK_SIZE;
    dy = 0;
  }

  if (yValue < 512 - threshold) {  
    dx = 0;
    dy = -SNAKE_BLOCK_SIZE;
  } else if (yValue > 512 + threshold) {  
    dx = 0;
    dy = SNAKE_BLOCK_SIZE;
  }
}

void moveSnake() {
  if (snakeLength >= SNAKE_MAX_LENGTH) {
    gameWin = true;
    return;
  }

 if (soundEnabled) {
  tone(BUZZER_PIN, currentToneFrequency, 10); 
}

  if (currentToneFrequency == 600) {
    currentToneFrequency = 800;
  } else if (currentToneFrequency == 800) {
    currentToneFrequency = 1000;
  } else if (currentToneFrequency == 1000) {
    currentToneFrequency = 600;
  }

  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dx;
  snakeY[0] += dy;
}

void checkCollision() {
  if (snakeX[0] < 0 || snakeX[0] >= SCREEN_WIDTH || snakeY[0] < 0 || snakeY[0] >= SCREEN_HEIGHT) {
    gameOver = true;
    return;
  }

  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
      return;
    }
  }
}

void checkFoodCollision() {
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    snakeX[snakeLength - 1] = snakeX[snakeLength - 2];
    snakeY[snakeLength - 1] = snakeY[snakeLength - 2];
    generateFood();
    if (soundEnabled) {
  tone(BUZZER_PIN, 1250, 200); 
}
  }
}

void generateFood() {
  bool validPosition = false;
  while (!validPosition) {
    foodX = random(0, (SCREEN_WIDTH / SNAKE_BLOCK_SIZE) - 8) * SNAKE_BLOCK_SIZE;
    foodY = random(0, (SCREEN_HEIGHT / SNAKE_BLOCK_SIZE) - 8) * SNAKE_BLOCK_SIZE;

    validPosition = true;
    for (int i = 0; i < snakeLength; i++) {
      if (snakeX[i] == foodX && snakeY[i] == foodY) {
        validPosition = false;
        break;
      }
    }
  }
}

void drawFood() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (foodPattern[i] & (1 << j)) {
        display.drawPixel(foodX + j, foodY + i, SSD1306_WHITE);
      }
    }
  }
}

void drawGame() {
  display.clearDisplay();

  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i], snakeY[i], SNAKE_BLOCK_SIZE, SNAKE_BLOCK_SIZE, SSD1306_WHITE);
  }

  drawFood();
  display.display();
}

void showGameOver() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 25);
  display.print("GAME OVER");
  display.display();
  delay(2000);  

  initMenu();  
  gameOver = false;
  gameStarted = false;  
}

void showYouWin() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 25);
  display.print("You Win");
  display.display();
  delay(2000);  

  initMenu();  
  gameWin = false;
  gameStarted = false;  
}

void resetGame() {
  gameOver = false;
  snakeLength = 5;
  dx = SNAKE_BLOCK_SIZE;
  dy = 0;
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = 64 - i * SNAKE_BLOCK_SIZE;
    snakeY[i] = 32;
  }
  generateFood();
}
