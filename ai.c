#include "ai.h"
#include <stdlib.h>
#include <string.h>

static const int WIN_PATTERNS[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
    {0, 4, 8}, {2, 4, 6}             // Diagonals
};

Node *create_node(const int state[9], int player) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
        return NULL;

    memcpy(node->game_state, state, sizeof(int) * 9);
    for (int i = 0; i < 9; i++) {
        node->actions[i] = NULL;
    }
    node->player = player;
    node->count = 0;

    return node;
}

void free_tree(Node *root) {
    if (!root)
        return;

    for (int i = 0; i < 9; i++) {
        if (root->actions[i] != NULL) {
            free_tree(root->actions[i]);
            root->actions[i] = NULL;
        }
    }
    free(root);
}

int check_terminal_state(const int state[9]) {
    for (int i = 0; i < 8; i++) {
        int a = WIN_PATTERNS[i][0];
        int b = WIN_PATTERNS[i][1];
        int c = WIN_PATTERNS[i][2];

        if (state[a] != 0 && state[a] == state[b] && state[b] == state[c]) {
            return state[a]; // 1 for X, 2 for O
        }
    }

    if (!is_moves_left(state)) {
        return 3; // Draw
    }

    return 0; // Game in progress
}

bool is_moves_left(const int state[9]) {
    for (int i = 0; i < 9; i++) {
        if (state[i] == 0) {
            return true;
        }
    }
    return false;
}

void build_game_tree(Node *root) {
    if (!root)
        return;

    if (check_terminal_state(root->game_state) != 0) {
        return;
    }

    int next_p = (root->player == 1) ? 2 : 1;

    for (int i = 0; i < 9; i++) {
        if (root->game_state[i] == 0) {
            int next_state[9];
            memcpy(next_state, root->game_state, sizeof(int) * 9);
            next_state[i] = root->player;

            Node *child = create_node(next_state, next_p);
            root->actions[i] = child;
            root->count++;
            build_game_tree(child);
        }
    }
}

int evaluate_board(const int state[9], int ai_player) {
    int terminal = check_terminal_state(state);
    int opponent = (ai_player == 1) ? 2 : 1;

    if (terminal == ai_player) {
        return +10;
    } else if (terminal == opponent) {
        return -10;
    }
    return 0;
}

int minimax(int state[9], int depth, bool is_maximizing, int ai_player) {
    int terminal = check_terminal_state(state);
    int opponent = (ai_player == 1) ? 2 : 1;

    if (terminal == ai_player) {
        return 10 - depth;
    }
    if (terminal == opponent) {
        return depth - 10;
    }
    if (terminal == 3) {
        return 0;
    }

    if (is_maximizing) {
        int best = -1000;
        for (int i = 0; i < 9; i++) {
            if (state[i] == 0) {
                state[i] = ai_player;
                int score = minimax(state, depth + 1, false, ai_player);
                state[i] = 0;
                if (score > best) {
                    best = score;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 9; i++) {
            if (state[i] == 0) {
                state[i] = opponent;
                int score = minimax(state, depth + 1, true, ai_player);
                state[i] = 0;
                if (score < best) {
                    best = score;
                }
            }
        }
        return best;
    }
}

int find_best_move(int state[9], int ai_player) {
    if (ai_player == 0) {
        ai_player = 1;
    }
    if (check_terminal_state(state) != 0) {
        return -1;
    }

    int best_val = -1000;
    int best_move = -1;

    for (int i = 0; i < 9; i++) {
        if (state[i] == 0) {
            state[i] = ai_player;
            int move_val = minimax(state, 0, false, ai_player);
            state[i] = 0;

            if (move_val > best_val) {
                best_move = i;
                best_val = move_val;
            }
        }
    }

    return best_move;
}
