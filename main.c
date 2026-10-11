#include <stdio.h>
#include <raylib.h>
#include "ai.h"
#include "engine.h"

#define WIDTH 800
#define HEIGHT 600

// Constants
const int board_size = 450;
const int cell_size = board_size / 3;
const int start_x = (WIDTH - board_size) / 2;
const int start_y = (HEIGHT - board_size) / 2;

int get_cell(Vector2 mouse) {

    if (mouse.x < start_x || mouse.x >= start_x + board_size ||
        mouse.y < start_y || mouse.y >= start_y + board_size) {
        return -1;
    }

    int col = (int)(mouse.x - start_x) / cell_size;
    int row = (int)(mouse.y - start_y) / cell_size;

    return row * 3 + col;
}
void draw_grid() {
    for (int i = 1; i < 3; i++) {
        DrawLine(start_x + i * cell_size, start_y, start_x + i * cell_size,
                 start_y + board_size, WHITE);
        DrawLine(start_x, start_y + i * cell_size, start_x + board_size,
                 start_y + i * cell_size, WHITE);
    }

    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        int cell_x = start_x + col * cell_size;
        int cell_y = start_y + row * cell_size;
        int padding = 30;

        if (game_state[i] == X) {
            DrawLine(cell_x + padding, cell_y + padding,
                     cell_x + cell_size - padding, cell_y + cell_size - padding,
                     RED);
            DrawLine(cell_x + cell_size - padding, cell_y + padding,
                     cell_x + padding, cell_y + cell_size - padding, RED);
        } else if (game_state[i] == O) {
            DrawCircleLines(cell_x + cell_size / 2, cell_y + cell_size / 2,
                            ((float)cell_size / 2 - padding), BLUE);
        }
    }
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Tic Tac Toe");
    SetTargetFPS(30);
    while (!WindowShouldClose()) {

        // Input handling
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            int index = get_cell(mouse);
            printf("CLICKED: %d\n", index);
            if (index != -1 && game_state[index] == EMPTY &&
                calculate_logic() == 0) {
                game_state[index] = (next_player == 0) ? X : O;
                next_player = !next_player;

                if (calculate_logic() == 0) {
                    int ai_piece = (next_player == 0) ? X : O;
                    int best_move = find_best_move(game_state, ai_piece);
                    printf("BEST: %d\n", best_move);
                    if (best_move != -1) {
                        game_state[best_move] = ai_piece;
                        next_player = !next_player;
                    }
                }
            }
        }

        if (IsKeyPressed(KEY_R)) {
            reset_game_state();
            next_player = 0;
        }

        // Game logic
        // TODO: The core game engine implementation
        int won = calculate_logic();

        // Render
        BeginDrawing();
        ClearBackground(DARKGRAY);
        draw_grid();
        if (won == 1) {
            DrawText("X has Won", WIDTH / 2, HEIGHT / 2, 23, WHITE);
        } else if (won == 2) {
            DrawText("O has Won", WIDTH / 2, HEIGHT / 2, 23, WHITE);
        } else if (won == 3) {
            DrawText("Draw", WIDTH / 2, HEIGHT / 2, 23, WHITE);
        }
        EndDrawing();
    }
    return 0;
}
