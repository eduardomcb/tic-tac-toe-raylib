#include "button.h"
#include "raylib.h"

void InitButton(Button *btn, Texture2D tex, Rectangle bounds,
                const char *text) {
  btn->texture = tex;
  btn->bounds = bounds;
  btn->text = text;
  btn->state = BTN_STATE_NORMAL;
  btn->action = false;

  btn->colorNormal = WHITE;
  btn->colorHover = LIGHTGRAY;
  btn->colorPressed = DARKGRAY;
  btn->colorText = WHITE;
}

void UpdateButton(Button *btn, Vector2 mousePoint) {
  btn->action = false;

  if (CheckCollisionPointRec(mousePoint, btn->bounds)) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      btn->state = BTN_STATE_PRESSED;
    } else {
      btn->state = BTN_STATE_HOVER;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      btn->action = true;
    }
  } else {
    btn->state = BTN_STATE_NORMAL;
  }
}

void DrawButton(const Button *btn, Font font, float fontSize, float spacing) {
  Color tint = btn->colorNormal;
  if (btn->state == BTN_STATE_HOVER)
    tint = btn->colorHover;
  if (btn->state == BTN_STATE_PRESSED)
    tint = btn->colorPressed;

  DrawTexture(btn->texture, (int)btn->bounds.x, (int)btn->bounds.y, tint);

  Vector2 textSize = MeasureTextEx(font, btn->text, fontSize, spacing);
  Vector2 textPos = {
      (btn->bounds.x + (btn->bounds.width / 2.0f)) - (textSize.x / 2.0f),
      (btn->bounds.y + (btn->bounds.height / 2.0f)) - (textSize.y / 2.0f)};

  DrawTextEx(font, btn->text, textPos, fontSize, spacing, btn->colorText);
}
