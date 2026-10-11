#include "engine.h"
#include <stdio.h>
#include <wctype.h>
int game_state[9] = {0};
int next_player = 0; // 0 for X and 1 for O
int winner = 0;      // 0 => game in progress, 1 => X, 2 => O

// Check for winner or draw
// Returns: 1 if X won, 2 if O won, 3 if draw, 0 if game is ongoing
int check_winner() {
    int win_patterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (int i = 0; i < 8; i++) {
        int a = win_patterns[i][0];
        int b = win_patterns[i][1];
        int c = win_patterns[i][2];

        if (game_state[a] != 0 && game_state[a] == game_state[b] &&
            game_state[b] == game_state[c]) {
            return game_state[a];
        }
    }

    for (int i = 0; i < 9; i++) {
        if (game_state[i] == 0) {
            return 0; // Game still in progress
        }
    }

    return 3; // Draw
}

// Applies a move at position (0-8) for the current player
// Returns: 1 if move was valid and played, 0 otherwise
int make_move(int pos) {
    if (pos < 0 || pos > 8 || game_state[pos] != 0) {
        return 0;
    }

    // 1 for X, 2 for O
    game_state[pos] = (next_player == 0) ? 1 : 2;
    next_player = 1 - next_player;
    return 1;
}

int calculate_logic() {
    // Check if the current board state has a conclusion
    winner = check_winner();
    if (winner == 1 || winner == 2)
        printf("Winner: %d\n", winner);
    return winner;
}

void reset_game_state() {
    for (int i = 0; i < 9; i++) {
        game_state[i] = EMPTY;
    }
    winner = 0;
    next_player = 0;
}
