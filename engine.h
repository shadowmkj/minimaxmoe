#pragma once

typedef enum { EMPTY, X, O } CellState; // State for each Cell

extern int next_player;
extern int game_state[9];
extern int winner;

int calculate_logic();
void reset_game_state();
