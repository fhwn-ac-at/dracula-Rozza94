#pragma once

#include <stdbool.h>

#define MAX_BOARD_WIDTH  10
#define MAX_BOARD_HEIGHT 10
#define MAX_BOARD_SIZE   (MAX_BOARD_WIDTH * MAX_BOARD_HEIGHT)
#define MAX_SNAKES       50
#define MAX_LADDERS      50

/// Represents either a snake or a ladder on the board.
typedef struct {
    int start;  // starting square
    int end;    // ending square (lower for snake, higher for ladder)
} Jump;

/// Represents the full board with its snakes and ladders.
typedef struct {
    int width;   // e.g., 10 for a 10x10 board
    int height;  // e.g., 10 for a 10x10 board
    int size;    // width * height

    Jump snakes[MAX_SNAKES];
    int num_snakes;

    Jump ladders[MAX_LADDERS];
    int num_ladders;
} Board;

/**
 * Initializes the board with given dimensions.
 * @param board Pointer to the board to initialize.
 * @param width Width of the board (e.g., 10).
 * @param height Height of the board (e.g., 10).
 */
void board_init(Board* board, int width, int height);

/**
 * Adds a snake to the board.
 * @param board Pointer to the board.
 * @param start Start position (must be > end).
 * @param end End position (must be < start).
 * @return true if added successfully, false otherwise.
 */
bool board_add_snake(Board* board, int start, int end);

/**
 * Adds a ladder to the board.
 * @param board Pointer to the board.
 * @param start Start position (must be < end).
 * @param end End position (must be > start).
 * @return true if added successfully, false otherwise.
 */
bool board_add_ladder(Board* board, int start, int end);

/**
 * Checks if the current square is a snake or ladder start.
 * If yes, returns the destination of the jump.
 * If not, returns the current position unchanged.
 * @param board Pointer to the board.
 * @param position Current player position.
 * @return New position after applying snake or ladder, or original.
 */
int board_apply_jump(const Board* board, int position);

/**
 * Checks whether a jump overlaps with any existing snake or ladder.
 * @param board Pointer to the board.
 * @param start Proposed start square.
 * @param end Proposed end square.
 * @return true if overlapping, false otherwise.
 */
bool board_is_conflict(const Board* board, int start, int end);

/**
 * Prints the current board configuration (for debugging).
 * @param board Pointer to the board.
 */
void board_print(const Board* board);

