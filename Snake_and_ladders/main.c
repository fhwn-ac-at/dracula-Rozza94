#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "dice.h"
#include "simulator.h"
#include "stats.h"
#include "config.h"  // جديد

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <board_config_file>\n", argv[0]);
        return 1;
    }

    const char* config_file = argv[1];

    Board board;
    if (!load_board_from_file(&board, config_file)) {
        fprintf(stderr, "❌ Failed to load board config from: %s\n", config_file);
        return 1;
    }

    board_print(&board);
    dice_init();

    const int NUM_GAMES = 1000;
    const int DIE_FACES = 6;
    bool use_non_uniform = false;
    int probabilities[MAX_DIE_FACES] = {1, 1, 1, 1, 1, 1};

    printf("\n🔁 Simulating %d games...\n", NUM_GAMES);
    double avg_moves = simulate_average_moves(&board, DIE_FACES, NUM_GAMES, use_non_uniform, probabilities);
    printf("📈 Average number of moves to win: %.2f\n", avg_moves);

    GameResult best_result;
    if (simulate_shortest_win(&board, DIE_FACES, NUM_GAMES, use_non_uniform, probabilities, &best_result)) {
        printf("\n🏆 Shortest winning game found in %d moves:\n", best_result.move_count);
        printf("    Roll sequence: ");
        for (int i = 0; i < best_result.move_count; i++) {
            printf("%d ", best_result.moves[i]);
        }
        printf("\n");
    } else {
        printf("\n⚠️ No winning game found during simulation.\n");
    }

    Stats stats;
    stats_init(&stats);
    for (int i = 0; i < NUM_GAMES; i++) {
        GameResult result;
        simulate_game(&board, DIE_FACES, &result, use_non_uniform, probabilities);
        stats_update(&board, &result, &stats);
    }

    stats_print(&board, &stats);
    return 0;
}
