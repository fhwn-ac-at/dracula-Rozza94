#include "simulator.h"
#include <stdio.h>
#include <string.h>

void simulate_game(
    const Board* board,
    int die_faces,
    GameResult* result,
    bool use_non_uniform,
    const int* probabilities
) {
    if (!board || !result) return;

    int position = 1;
    int moves = 0;

    result->won = false;
    result->move_count = 0;
    memset(result->moves, 0, sizeof(result->moves));

    while (moves < MAX_MOVES_TRACKED) {
        int roll = use_non_uniform
                 ? dice_roll_non_uniform(die_faces, probabilities)
                 : dice_roll_uniform(die_faces);

        result->moves[moves++] = roll;
        position += roll;

        // إذا تجاوزنا اللوح، نبقى في مكاننا
        if (position > board->size) {
            position -= roll;
        } else {
            position = board_apply_jump(board, position);
        }

        if (position == board->size) {
            result->won = true;
            break;
        }
    }

    result->move_count = moves;
}

double simulate_average_moves(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities
) {
    if (!board || num_games <= 0) return 0.0;

    int total_moves = 0;
    int wins = 0;

    for (int i = 0; i < num_games; i++) {
        GameResult res;
        simulate_game(board, die_faces, &res, use_non_uniform, probabilities);
        if (res.won) {
            total_moves += res.move_count;
            wins++;
        }
    }

    if (wins == 0) return 0.0; // لم يتم تحقيق أي فوز

    return (double)total_moves / wins;
}

bool simulate_shortest_win(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities,
    GameResult* out_result
) {
    if (!board || !out_result || num_games <= 0) return false;

    bool found = false;
    int min_moves = MAX_MOVES_TRACKED;
    GameResult temp;

    for (int i = 0; i < num_games; i++) {
        simulate_game(board, die_faces, &temp, use_non_uniform, probabilities);
        if (temp.won && temp.move_count < min_moves) {
            min_moves = temp.move_count;
            *out_result = temp;
            found = true;
        }
    }

    return found;
}
