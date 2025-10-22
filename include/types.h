#ifndef TYPES_H
#define TYPES_H
#include "raylib.h"
#include <stdbool.h>

typedef enum {
  SCREEN_MENU,
  SCREEN_PLAYING,
  SCREEN_SCOREBOARD,
  SCREEN_OVER
} GameScreen;

typedef enum {
  BTN_STATE_NORMAL,
  BTN_STATE_HOVER,
  BTN_STATE_PRESSED
} ButtonState;


typedef struct {
  GameScreen currentScreen;
  Font font;
  Texture2D texButton;
  Texture2D texBackground;
} GameState;

#endif
