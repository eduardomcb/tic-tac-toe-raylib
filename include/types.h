#ifndef TYPES_H
#define TYPES_H
#include "raylib.h"
#include <stdbool.h>

typedef enum {
  SCREEN_MENU,
  SCREEN_PLAYING,
  SCREEN_SCOREBOARD,
  SCREEN_OVER,
  SCREEN_EXIT
} GameScreen;

typedef enum {
  BTN_STATE_NORMAL,
  BTN_STATE_HOVER,
  BTN_STATE_PRESSED
} ButtonState;

typedef struct {
  Rectangle bounds;
  Texture2D texture;
  const char *text;
  ButtonState state;
  bool action;

  Color colorNormal;
  Color colorHover;
  Color colorPressed;
  Color colorText;
} Button;

typedef struct {
  GameScreen currentScreen;
  Font font;
  Texture2D texButton;
  Texture2D texBackground;

  Button btnPlay;
  Button btnScoreboard;
  Button btnExit;

} GameState;

#endif
