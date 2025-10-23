#include "button.h"
#include "constants.h"
#include "raylib.h"
#include "types.h"
#include <stdlib.h>

int main(void) {

  /*antes do while temos as funções, estruturas e variaveis que precisam ser
    inicaalizadas*/
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

  Vector2 mousePoint = {0.0f, 0.0f};

  GameState *game = malloc(sizeof(GameState));
  game->font = LoadFont("assets/fonts/kenney-future-narrow.ttf");
  game->texButton =
      LoadTexture("assets/images/ui/button_rectangle_depth_flat.png");

  game->currentScreen = SCREEN_MENU;

  float btnWidth = game->texButton.width;
  float btnHeight = game->texButton.height;

  //Botão iniciar
  Rectangle playBounds = {(SCREEN_WIDTH / 2.0f) - (btnWidth / 2.0f),SCREEN_HEIGHT / 2.0f - btnHeight * 1.5f, btnWidth,btnHeight};
  InitButton(&game->btnPlay, game->texButton, playBounds, "Iniciar Jogo");

  //Botão Placar
  Rectangle scoreBounds = {playBounds.x , playBounds.y + playBounds.height + 20.0f, btnWidth, btnHeight};
  InitButton(&game->btnScoreboard, game->texButton, scoreBounds, "Placar");

  //Botão Sair
  Rectangle exitBounds = {scoreBounds.x , scoreBounds.y + scoreBounds.height + 20.0f,btnWidth, btnHeight};
  InitButton(&game->btnExit, game->texButton, exitBounds, "Sair");

  while (!WindowShouldClose()) {

    // switch para funções de updates para cada tela/etapa
    switch (game->currentScreen) {
    case SCREEN_MENU:
      mousePoint = GetMousePosition();

      Vector2 textSize = MeasureTextEx(game -> font, "Tic  tac  toe - UFAL", 60.0f, 1.0f);
      float textWidth = textSize.x;

      float textPosX = (SCREEN_WIDTH / 2.0f) - (textWidth / 2.0f);

      DrawTextEx(game -> font, "Tic  tac  toe - UFAL", (Vector2){textPosX, 50},60.0f,1.0f,DARKGREEN);

      UpdateButton(&game->btnPlay, mousePoint);
      UpdateButton(&game->btnScoreboard, mousePoint);
      UpdateButton(&game->btnExit, mousePoint);
      break;
    case SCREEN_PLAYING:

      break;
    case SCREEN_SCOREBOARD:
      break;
    case SCREEN_OVER:
      break;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // switch para desenhar na tela para cada tela/etapa
    switch (game->currentScreen) {
    case SCREEN_MENU:
      DrawButton(&game->btnPlay, game->font, BUTTON_TEXT_FONT_SIZE, 1.0f);
      DrawButton(&game->btnScoreboard, game->font, BUTTON_TEXT_FONT_SIZE, 1.0f);
      DrawButton(&game->btnExit, game->font, BUTTON_TEXT_FONT_SIZE, 1.0f);
      break;
    case SCREEN_PLAYING:
      DrawText("Tela da jogatinha", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 24.0f,
               BLACK);
      break;
    case SCREEN_SCOREBOARD:
      DrawText("Tela de visualizar placar", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
               24.0f, BLACK);
      break;
    case SCREEN_OVER:
      DrawText("Tela de fim de jogo", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
               24.0f, BLACK);
      break;
    }

    EndDrawing();
  }

  UnloadTexture(game->texButton);
  UnloadFont(game->font);
  free(game);
  CloseWindow();

  return 0;
}
