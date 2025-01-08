#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "constants.h"
#include "game.h"
#include "menu.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

volatile bool joyPressed = false;  
int snakeSpeed = 200;              
unsigned long lastMoveTime = 0;    

void joyInterrupt() {
  joyPressed = true;
}

void handleJoystickPress() {
  if (!gameStarted) {
    gameStarted = true;  
    resetGame();          
  }
}

void setup() {
  pinMode(JOY_SEL, INPUT_PULLUP); 
  pinMode(BUZZER_PIN, OUTPUT);    

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.display();

  initMenu(); 
  attachInterrupt(digitalPinToInterrupt(JOY_SEL), joyInterrupt, FALLING); 
}

void loop() {
  static MenuState lastMenuState = PLAY; 

  if (!gameStarted) {
    menuLoop(); 
    return;     
  }

  if (gameOver) {
    showGameOver(); 
    return;
  }
  if (gameWin) {
    showYouWin(); 
    return;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastMoveTime >= snakeSpeed) {
    handleInput();
    moveSnake();          
    checkCollision();     
    checkFoodCollision(); 
    drawGame();           
    lastMoveTime = currentTime; 
  }

  if (joyPressed) {
    joyPressed = false;  
    handleJoystickPress();  
  }

  if (currentMenuState != lastMenuState) {
    switch (currentMenuState) {
      case EASY:
        snakeSpeed = 300; 
        break;
      case MEDIUM:
        snakeSpeed = 200; 
        break;
      case HARD:
        snakeSpeed = 100; 
        break;
      default:
        break;
    }
    lastMenuState = currentMenuState;
  }
}
