#include "stats.h"
#include <stdio.h>
#include <string.h>

void stats_init(Stats* stats) {
    if (!stats) return;

    memset(stats->snake_hits, 0, sizeof(stats->snake_hits));
    memset(stats->ladder_hits, 0, sizeof(stats->ladder_hits));
    stats->total_games = 0;
}

void stats_update(const Board* board, const GameResult* result, Stats* stats) {
    if (!board || !result || !stats || !result->won) return;

    int position = 1;
    for (int i = 0; i < result->move_count; i++) {
        int roll = result->moves[i];
        int next = position + roll;

        if (next > board->size) {
            // تجاوزنا اللوح، لا نتحرك
            next = position;
        }

        // تحقق مما إذا كان هناك سلم أو ثعبان
        int jumped = board_apply_jump(board, next);

        if (jumped != next) {
            // تحقق هل هو سلم أم ثعبان؟
            for (int j = 0; j < board->num_snakes; j++) {
                if (board->snakes[j].start == next && board->snakes[j].end == jumped) {
                    stats->snake_hits[j]++;
                    break;
                }
            }

            for (int j = 0; j < board->num_ladders; j++) {
                if (board->ladders[j].start == next && board->ladders[j].end == jumped) {
                    stats->ladder_hits[j]++;
                    break;
                }
            }

            position = jumped;
        } else {
            position = next;
        }
    }

    stats->total_games++;
}

void stats_print(const Board* board, const Stats* stats) {
    if (!board || !stats) return;

    printf("\n📊 Snake and Ladder Usage Statistics (across %d games):\n", stats->total_games);

    printf("\n🐍 Snakes:\n");
    for (int i = 0; i < board->num_snakes; i++) {
        int count = stats->snake_hits[i];
        double freq = (stats->total_games > 0) ? ((double)count / stats->total_games) : 0.0;
        printf("  Snake %2d: from %3d to %3d — used %4d times (%.2f per game)\n",
               i + 1, board->snakes[i].start, board->snakes[i].end, count, freq);
    }

    printf("\n🪜 Ladders:\n");
    for (int i = 0; i < board->num_ladders; i++) {
        int count = stats->ladder_hits[i];
        double freq = (stats->total_games > 0) ? ((double)count / stats->total_games) : 0.0;
        printf("  Ladder %2d: from %3d to %3d — used %4d times (%.2f per game)\n",
               i + 1, board->ladders[i].start, board->ladders[i].end, count, freq);
    }
}
