#include "constants.h"
#include "game.h"
#include "raylib.h"
#include "types.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

  GameState game = {0};
  InitGame(&game);

  while (!WindowShouldClose()) {

    UpdateGame(&game);

    DrawGame(&game);
  }

  CleanupGame(&game);
  CloseWindow();

  return 0;
}
