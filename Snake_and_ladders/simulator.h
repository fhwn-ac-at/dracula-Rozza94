#pragma once

#include "board.h"
#include "graph.h"
#include "dice.h"
#include <stdbool.h>

#define MAX_MOVES_TRACKED (MAX_BOARD_SIZE * 2)

/**
 * Represents the result of a single game simulation.
 */
typedef struct {
    int move_count;                    // عدد الرميات في هذه المحاكاة
    int moves[MAX_MOVES_TRACKED];     // تسلسل رميات النرد
    bool won;                          // true إذا وصل اللاعب إلى نهاية اللوح
} GameResult;

/**
 * Simulates a single game of Snakes and Ladders.
 * 
 * @param board Pointer to the board structure.
 * @param die_faces Number of faces on the die.
 * @param result Output: structure containing result details.
 * @param use_non_uniform Whether to use non-uniform die.
 * @param probabilities If non-uniform is enabled, array of die probabilities (length = die_faces).
 */
void simulate_game(
    const Board* board,
    int die_faces,
    GameResult* result,
    bool use_non_uniform,
    const int* probabilities
);

/**
 * Simulates multiple games and calculates average number of moves.
 * 
 * @param board Pointer to the board.
 * @param die_faces Number of die faces.
 * @param num_games Number of games to simulate.
 * @param use_non_uniform Use weighted die?
 * @param probabilities Optional array of weights if using non-uniform.
 * @return Average number of moves to win.
 */
double simulate_average_moves(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities
);

/**
 * Simulates multiple games and finds the shortest win sequence.
 * 
 * @param board Pointer to the board.
 * @param die_faces Number of die faces.
 * @param num_games Number of simulations to run.
 * @param use_non_uniform Use weighted die?
 * @param probabilities Optional array of weights.
 * @param out_result Pointer to where the shortest result will be stored.
 * @return true if a winning game was found, false otherwise.
 */
bool simulate_shortest_win(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities,
    GameResult* out_result
);
