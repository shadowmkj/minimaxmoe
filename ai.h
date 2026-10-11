
#pragma once

#include <stdbool.h>

typedef struct Node {
    int game_state[9];
    struct Node *actions[9];
    int player;
    int count;
} Node;

// Tree management
Node *create_node(const int state[9], int player);
void free_tree(Node *root);
void build_game_tree(Node *root);

// Game evaluation helpers
int evaluate_board(const int state[9], int ai_player);
int check_terminal_state(const int state[9]);
bool is_moves_left(const int state[9]);

// AI decision algorithms
int minimax(int state[9], int depth, bool is_maximizing, int ai_player);
int find_best_move(int state[9], int ai_player);
