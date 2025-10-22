#ifndef GAME_H
#define GAME_H

#include "types.h"

void InitGame(GameState *game);

void UpdateGame(GameState *game);

void DrawGame(const GameState *game);

void CleanupGame(GameState *game);

#endif
