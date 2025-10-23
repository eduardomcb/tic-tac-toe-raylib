#include "button.h"
#include "constants.h"
#include "raylib.h"
#include "types.h"
#include <stdlib.h>

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

  Vector2 mousePoint = {0.0f, 0.0f};

  GameState *game = malloc(sizeof(GameState));
  game->font = LoadFont("assets/fonts/kenney-future-narrow.ttf");
  game->texButton =
      LoadTexture("assets/images/ui/button_rectangle_depth_flat.png");

  float btnWidth = game->texButton.width;
  float btnHeight = game->texButton.height;

  Rectangle playBounds = {(SCREEN_WIDTH / 2.0f) - (btnWidth / 2.0f),
                          SCREEN_HEIGHT / 2.0f - btnHeight * 1.5f, btnWidth,
                          btnHeight};
  InitButton(&game->btnPlay, game->texButton, playBounds, "Iniciar Jogo");

  while (!WindowShouldClose()) {

    mousePoint = GetMousePosition();

    UpdateButton(&game->btnPlay, mousePoint);
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawButton(&game->btnPlay, game->font, BUTTON_TEXT_FONT_SIZE, 1.0f);

    EndDrawing();
  }

  UnloadTexture(game->texButton);
  UnloadFont(game->font);
  free(game);
  CloseWindow();

  return 0;
}
