#include "button.h"
#include "constants.h"
#include "game.h"
#include "raylib.h"
#include "types.h"

static void UpdateMenu(GameState *game);
static void DrawMenu(const GameState *game);

void InitGame(GameState *game) {
  game->font = LoadFont("assets/fonts/kenney-future-narrow.ttf");
  game->texButton =
      LoadTexture("assets/images/ui/button_rectangle_depth_flat.png");

  game->currentScreen = SCREEN_MENU;

  float btnWidth = game->texButton.width;
  float btnHeight = game->texButton.height;

  // Botão iniciar
  Rectangle playBounds = {(SCREEN_WIDTH / 2.0f) - (btnWidth / 2.0f),
                          SCREEN_HEIGHT / 2.0f - btnHeight * 1.5f, btnWidth,
                          btnHeight};
  InitButton(&game->btnPlay, game->texButton, playBounds, "Iniciar Jogo");

  // Botão Placar
  Rectangle scoreBounds = {playBounds.x,
                           playBounds.y + playBounds.height + 20.0f, btnWidth,
                           btnHeight};
  InitButton(&game->btnScoreboard, game->texButton, scoreBounds, "Placar");

  // Botão Sair
  Rectangle exitBounds = {scoreBounds.x,
                          scoreBounds.y + scoreBounds.height + 20.0f, btnWidth,
                          btnHeight};
  InitButton(&game->btnExit, game->texButton, exitBounds, "Sair");
}

void UpdateGame(GameState *game) {
  switch (game->currentScreen) {
  case SCREEN_MENU:
    UpdateMenu(game);
    break;
  case SCREEN_PLAYING:
    break;
  case SCREEN_SCOREBOARD:
    break;
  case SCREEN_OVER:
    break;
  }
}

void DrawGame(const GameState *game) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  switch (game->currentScreen) {
  case SCREEN_MENU:
    DrawMenu(game);
    break;
  case SCREEN_PLAYING:
    break;
  case SCREEN_SCOREBOARD:
    break;
  case SCREEN_OVER:
    break;
  }

  EndDrawing();
}

void CleanupGame(GameState *game) {
  UnloadTexture(game->texButton);
  UnloadFont(game->font);
}

static void UpdateMenu(GameState *game) {
  Vector2 mousePos = GetMousePosition();
  UpdateButton(&game->btnPlay, mousePos);
  UpdateButton(&game->btnScoreboard, mousePos);
  UpdateButton(&game->btnExit, mousePos);

  if (game->btnPlay.action) {
    game->currentScreen = SCREEN_PLAYING;
  }
  if (game->btnScoreboard.action) {
    game->currentScreen = SCREEN_SCOREBOARD;
  }
  if (game->btnExit.action) {
    game->currentScreen = SCREEN_EXIT;
  }
}

static void DrawMenu(const GameState *game) {
  Vector2 textSize = MeasureTextEx(game->font, GAME_TITLE, 60.0f, 1.0f);
  float textWidth = textSize.x;

  float textPosX = (SCREEN_WIDTH / 2.0f) - (textWidth / 2.0f);

  DrawTextEx(game->font, GAME_TITLE, (Vector2){textPosX, 50}, 60.0f, 1.0f,
             DARKGREEN);

  DrawButton(&game->btnPlay, game->font, BUTTON_TEXT_FONT_SIZE, 1.0f);
  DrawButton(&game->btnScoreboard, game->font, BUTTON_TEXT_FONT_SIZE, 1.0f);
  DrawButton(&game->btnExit, game->font, BUTTON_TEXT_FONT_SIZE, 1.0f);
}
