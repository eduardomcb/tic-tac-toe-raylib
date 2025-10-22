#include "constants.h"
#include "raylib.h"
#include "types.h"

//botão de exemplo
bool button(Rectangle bounds, const char *text, Texture2D texture, Font font,
            float fontSize, Color colorText) {
  Vector2 mousePoint = GetMousePosition();
  ButtonState state = BTN_STATE_NORMAL;
  bool action = false;

  if (CheckCollisionPointRec(mousePoint, bounds)) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      state = BTN_STATE_PRESSED;
    else
      state = BTN_STATE_HOVER;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
      action = true;
  }

  Color tint = WHITE;
  if (state == BTN_STATE_HOVER)
    tint = LIGHTGRAY;
  if (state == BTN_STATE_PRESSED)
    tint = DARKGRAY;
  DrawTexture(texture, (int)bounds.x, (int)bounds.y, tint);

  // float fontSize = 40.0f;
  float spacing = 1.0f;

  Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);

  float textPosX = (bounds.x + (bounds.width / 3.f)) - (textSize.x / 2.0f);
  float textPosY = (bounds.y + (bounds.height / 3.f)) - (textSize.y / 2.0f);

  DrawTextEx(font, text, (Vector2){textPosX, textPosY}, fontSize, spacing,
             colorText);

  return action;
}

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

  Font kenneyFont = LoadFont("assets/fonts/sua_fonte_do_kenney.ttf");
  Texture2D texButton =
      LoadTexture("assets/images/ui/button_rectangle_depth_flat.png");

  Rectangle btnStartBounds = {(SCREEN_WIDTH / 2.0f) - (texButton.width / 2.0f),
                              SCREEN_HEIGHT / 2.0f - texButton.height - 10,
                              (float)texButton.width, (float)texButton.height};

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (button(btnStartBounds, "Começar", texButton, kenneyFont, 40, WHITE)) {
      TraceLog(LOG_INFO, "A Partida vai começar");
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
