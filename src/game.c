#include "button.h"
#include "constants.h"
#include "game.h"
#include "raylib.h"
#include "types.h"

static void UpdateMenu(GameState *game);
static void DrawMenu(const GameState *game);
static void UpdatePlaying(GameState *game);
static void DrawPlaying(const GameState *game);

static void ResetGame(GameState *game);
static void MakePlayerMove(GameState *game, int row, int col);
static void MakeAIMove(GameState *game);

void InitGame(GameState *game) {
  game->font = LoadFont("assets/fonts/kenney-future-narrow.ttf");
  game->texButton =
      LoadTexture("assets/images/ui/button_rectangle_depth_flat.png");

  game->texCell = LoadTexture("assets/images/ui/check_square_grey.png");
  game->texPlayerX = LoadTexture("assets/images/ui/icon_cross.png");
  game->texPlayerO = LoadTexture("assets/images/ui/icon_circle.png");

  game->currentScreen = SCREEN_MENU;

  /* pegando o tamanho da textura real para usar como referencia no calculo de
  tamanho*/
  float cellWidth = game->texCell.width;
  float cellHeight = game->texCell.height;

  float totalGridWidth =
      (BOARD_SIZE * cellWidth) + ((BOARD_SIZE - 1) * CELL_SPACING);
  float totalGridHeight =
      (BOARD_SIZE * cellHeight) + ((BOARD_SIZE - 1) * CELL_SPACING);

  float startX = (SCREEN_WIDTH - totalGridWidth) / 2.0f;
  float startY = (SCREEN_HEIGHT - totalGridHeight) / 2.0f;

  for (int i = 0; i < BOARD_SIZE; i++) {   // Linhas (i)
    for (int j = 0; j < BOARD_SIZE; j++) { // Colunas (j)

      float cellX = startX + (j * (cellWidth + CELL_SPACING));
      float cellY = startY + (i * (cellHeight + CELL_SPACING));

      game->boardRects[i][j] = (Rectangle){cellX, cellY, cellWidth, cellHeight};
    }
  }

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

  ResetGame(game);
}

void UpdateGame(GameState *game) {
  switch (game->currentScreen) {
  case SCREEN_MENU:
    UpdateMenu(game);
    break;
  case SCREEN_PLAYING:
    UpdatePlaying(game);
    break;
  case SCREEN_SCOREBOARD:
    break;
  case SCREEN_EXIT:
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
    DrawPlaying(game);
    break;
  case SCREEN_SCOREBOARD:
    break;
  case SCREEN_EXIT:
    break;
  }

  EndDrawing();
}

void CleanupGame(GameState *game) {
  UnloadTexture(game->texButton);
  UnloadFont(game->font);
  UnloadTexture(game->texCell);
  UnloadTexture(game->texPlayerX);
  UnloadTexture(game->texPlayerO);
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

static void UpdatePlaying(GameState *game) {
  if (IsKeyPressed(KEY_M)) {
    game->currentScreen = SCREEN_MENU;
    return;
  }
  if (game->winner != 0) {
    if (IsKeyPressed(KEY_R))
      ResetGame(game);
    return;
  }

  if (game->currentPlayer == PLAYER_TURN) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mouse = GetMousePosition();

      for (int i = 0; i < BOARD_SIZE; i++) {   // linha
        for (int j = 0; j < BOARD_SIZE; j++) { // coluna
          if (CheckCollisionPointRec(mouse, game->boardRects[i][j])) {
            MakePlayerMove(game, i, j);
            return;
          }
        }
      }
    }
  } else if (game->currentPlayer == AI_TURN) {
    MakeAIMove(game);
  }
}

static void DrawPlaying(const GameState *game) {
  const char *title = "Humano (X) vs. Maquina (O)";
  Vector2 titleSize = MeasureTextEx(game->font, title, 30, TEXT_SPACING);
  DrawTextEx(game->font, title,
             (Vector2){(SCREEN_WIDTH / 2.0f) - (titleSize.x / 2.0f), 20}, 30,
             TEXT_SPACING, BLACK);

  for (int i = 0; i < BOARD_SIZE; i++) {   // para a linha
    for (int j = 0; j < BOARD_SIZE; j++) { // for para colunaa

      Rectangle rect = game->boardRects[i][j];
      char marker = game->board[i][j];

      DrawTextureEx(game->texCell, (Vector2){rect.x, rect.y}, 0.0f, 1.5f,
                    WHITE);

      Texture2D markerTex = {0};
      if (marker == PLAYER_MARKER) {
        markerTex = game->texPlayerX;
      } else if (marker == AI_MARKER) {
        markerTex = game->texPlayerO;
      }

      if (markerTex.id != 0) {
        int texX = (int)(rect.x + (rect.width - markerTex.width) / 1.5f);
        int texY = (int)(rect.y + (rect.height - markerTex.height) / 1.5f);
        // DrawTexture(markerTex, texX, texY, WHITE);
        DrawTextureEx(markerTex, (Vector2){texX, texY}, 0.0f, 1.5f, WHITE);
      }
    }
  }

  if (game->winner != 0) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                  (Color){250, 250, 250, 220});
    const char *winnerText = "";
    if (game->winner == PLAYER_TURN)
      winnerText = "Você Venceu!";
    else if (game->winner == AI_TURN)
      winnerText = "A Máquina Venceu!";
    else if (game->winner == 3)
      winnerText = "Empate!";

    Vector2 textSize = MeasureTextEx(game->font, winnerText, 40, TEXT_SPACING);
    DrawTextEx(game->font, winnerText,
               (Vector2){(SCREEN_WIDTH / 2.0f) - (textSize.x / 2.0f),
                         (SCREEN_HEIGHT / 2.0f) - 30},
               40, TEXT_SPACING, BLACK);
    const char *resetText = "Pressione 'R' para jogar novamente";
    Vector2 resetSize = MeasureTextEx(game->font, resetText, 20, TEXT_SPACING);
    DrawTextEx(game->font, resetText,
               (Vector2){(SCREEN_WIDTH / 2.0f) - (resetSize.x / 2.0f),
                         (SCREEN_HEIGHT / 2.0f) + 20},
               20, TEXT_SPACING, DARKGRAY);
  }

  DrawTextEx(game->font, "Pressione M para voltar ao Menu",
             (Vector2){10, SCREEN_HEIGHT - 30}, 20, TEXT_SPACING, GRAY);
}

static void ResetGame(GameState *game) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      game->board[i][j] = EMPTY_CELL;
    }
  }
  game->currentPlayer = PLAYER_TURN;
  game->winner = 0;
}

static void CheckForWin(GameState *game, int playerWhoMoved) {
  char marker = (playerWhoMoved == PLAYER_TURN) ? PLAYER_MARKER : AI_MARKER;

  for (int i = 0; i < BOARD_SIZE; i++) {
    if ((game->board[i][0] == marker && game->board[i][1] == marker &&
         game->board[i][2] == marker) ||
        (game->board[0][i] == marker && game->board[1][i] == marker &&
         game->board[2][i] == marker)) {
      game->winner = playerWhoMoved;
      return;
    }
  }

  if ((game->board[0][0] == marker && game->board[1][1] == marker &&
       game->board[2][2] == marker) ||
      (game->board[0][2] == marker && game->board[1][1] == marker &&
       game->board[2][0] == marker)) {
    game->winner = playerWhoMoved;
    return;
  }

  bool draw = true;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (game->board[i][j] == EMPTY_CELL) {
        draw = false;
        break;
      }
    }
    if (!draw)
      break;
  }

  if (draw) {
    game->winner = 3;
  }
}

static void MakePlayerMove(GameState *game, int row, int col) {
  if (game->board[row][col] == EMPTY_CELL) {

    game->board[row][col] = PLAYER_MARKER;

    CheckForWin(game, PLAYER_TURN);

    if (game->winner == 0) {
      game->currentPlayer = AI_TURN;
    }
  }
}

static void MakeAIMove(GameState *game) {
  Vector2 emptyCells[9];
  int count = 0;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (game->board[i][j] == EMPTY_CELL) {
        emptyCells[count] = (Vector2){(float)i, (float)j};
        count++;
      }
    }
  }

  if (count > 0) {
    int choice = GetRandomValue(0, count - 1);
    int row = (int)emptyCells[choice].x;
    int col = (int)emptyCells[choice].y;

    game->board[row][col] = AI_MARKER;

    CheckForWin(game, AI_TURN);

    if (game->winner == 0) {
      game->currentPlayer = PLAYER_TURN;
    }
  }
}
