#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "menu.h"
#include "constants.h"
#include "game.h"

extern Adafruit_SSD1306 display;

MenuState currentMenuState = PLAY;  
bool gameStarted = false;  
bool soundEnabled = true; 

void initMenu() {
  display.clearDisplay();
  display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

void menuLoop() {
  static unsigned long lastInputTime = 0;  
  unsigned long currentTime = millis();  

  if (currentTime - lastInputTime > 300) {  
    int yValue = analogRead(JOY_VER);
    int threshold = 50;  

    if (yValue > 512 + threshold) {  
      if (currentMenuState == PLAY) {
        currentMenuState = MUSIC;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_music, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == DIFFICULTY) {
        currentMenuState = PLAY;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      }
    } else if (yValue < 512 - threshold) {  
      if (currentMenuState == PLAY) {
        currentMenuState = DIFFICULTY;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_difficulty, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == MUSIC) {
        currentMenuState = PLAY;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      }
    }

    if (yValue < 512 - threshold) {  
      if (currentMenuState == OFF) {
        currentMenuState = ON;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_on, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      }
    } else if (yValue > 512 + threshold) {  
      if (currentMenuState == ON) {
        currentMenuState = OFF;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_off, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      }
    }

    if (yValue > 512 + threshold) {  
      if (currentMenuState == MEDIUM) {
        currentMenuState = HARD;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_hard, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == EASY) {
        currentMenuState = MEDIUM;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_medium, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      }
    } else if (yValue < 512 - threshold) {  
      if (currentMenuState == MEDIUM) {
        currentMenuState = EASY;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_easy, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == HARD) {
        currentMenuState = MEDIUM;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_medium, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      }
    }

    if (digitalRead(JOY_SEL) == LOW) {
      if (currentMenuState == PLAY && !gameStarted) {
        gameStarted = true;  
        resetGame();
      } else if (currentMenuState == MUSIC) {
        currentMenuState = ON;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_on, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == ON) {
        soundEnabled = true;  
        currentMenuState = PLAY;  
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == OFF) {
        soundEnabled = false;  
        currentMenuState = PLAY;  
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == DIFFICULTY) {
        currentMenuState = MEDIUM;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_medium, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == MEDIUM) {
        snakeSpeed = 200;
        currentMenuState = PLAY;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
      } else if (currentMenuState == EASY) {
        snakeSpeed = 300;
        currentMenuState = PLAY;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
    } else if (currentMenuState == HARD) {
        snakeSpeed = 100;
        currentMenuState = PLAY;
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_play, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.display();
     }
    }
    lastInputTime = currentTime;
  }
}
