#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>  

// Configurations for OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Joystick pins
#define JOY_VER A0    
#define JOY_HORZ A1   
#define JOY_SEL 2     

#define BUZZER_PIN 9

// Snake game configurations
#define SNAKE_MAX_LENGTH 10
#define SNAKE_BLOCK_SIZE 4

// Food pattern (8x8 pixels)
extern const uint8_t foodPattern[8];  

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 8320)
extern const uint8_t epd_bitmap_allArray_LEN;
extern const uint8_t epd_bitmap_play[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
extern const uint8_t epd_bitmap_music[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
extern const uint8_t epd_bitmap_difficulty[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
extern const uint8_t epd_bitmap_easy[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
extern const uint8_t epd_bitmap_medium[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
extern const uint8_t epd_bitmap_hard[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
extern const uint8_t epd_bitmap_on[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
extern const uint8_t epd_bitmap_off[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
;
#endif
