#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "types.h"

void InitButton(Button *btn, Texture2D tex, Rectangle bounds, const char *text);

void UpdateButton(Button *btn, Vector2 mousePoint);

void DrawButton(const Button *btn, Font font, float fontSize, float spacing);

#endif
