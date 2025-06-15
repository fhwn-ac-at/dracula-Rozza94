#pragma once

#include "board.h"
#include "simulator.h"

/**
 * Represents traversal statistics for snakes and ladders.
 */
typedef struct {
    int snake_hits[MAX_SNAKES];   // عدد مرات النزول عبر كل ثعبان
    int ladder_hits[MAX_LADDERS]; // عدد مرات الصعود عبر كل سلم
    int total_games;              // عدد الألعاب المحاكاة
} Stats;

/**
 * Initializes the stats structure.
 * @param stats Pointer to the stats object.
 */
void stats_init(Stats* stats);

/**
 * Updates stats with a new game result.
 * Traverses the move sequence and records which snakes/ladders were used.
 * 
 * @param board Pointer to the board used.
 * @param result The completed game result to analyze.
 * @param stats Pointer to the stats structure to update.
 */
void stats_update(const Board* board, const GameResult* result, Stats* stats);

/**
 * Prints statistics about how often each snake and ladder was used.
 * @param board Pointer to the board.
 * @param stats Pointer to the stats structure.
 */
void stats_print(const Board* board, const Stats* stats);
