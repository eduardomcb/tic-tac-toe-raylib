#include "raylib.h"

int main(void) {
  InitWindow(800, 450, "Tic Tac Toe - UFAL");

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Olá mundo", 10, 40, 20, DARKGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
