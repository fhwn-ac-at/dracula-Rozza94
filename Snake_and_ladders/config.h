#pragma once

#include "board.h"
#include <stdbool.h>

/**
 * Loads a board configuration from a text file.
 *
 * @param board Pointer to the board to initialize and fill.
 * @param filename Path to the configuration file (e.g., "board1.cfg").
 * @return true if the file was successfully loaded, false otherwise.
 */
bool load_board_from_file(Board* board, const char* filename);
