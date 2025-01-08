#ifndef MENU_H
#define MENU_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "constants.h"

extern Adafruit_SSD1306 display;

typedef enum {
  PLAY,
  MUSIC,
  DIFFICULTY,
  ON,
  OFF,
  EASY,    
  MEDIUM,  
  HARD     
} MenuState;

extern bool soundEnabled; 
extern int snakeSpeed; 

extern MenuState currentMenuState;  
extern bool gameStarted;  

void initMenu();
void menuLoop();

#endif
