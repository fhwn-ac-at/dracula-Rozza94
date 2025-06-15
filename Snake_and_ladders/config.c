#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool load_board_from_file(Board* board, const char* filename) {
    if (!board || !filename) return false;

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open board configuration file");
        return false;
    }

    char line[256];
    int width = 10, height = 10;
    bool board_initialized = false;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || strlen(line) < 2)
            continue;

        int start, end;

        if (sscanf(line, "BOARD %d %d", &width, &height) == 2) {
            board_init(board, width, height);
            board_initialized = true;
        } else if (sscanf(line, "LADDER %d %d", &start, &end) == 2) {
            if (!board_initialized) board_init(board, width, height);
            board_add_ladder(board, start, end);
        } else if (sscanf(line, "SNAKE %d %d", &start, &end) == 2) {
            if (!board_initialized) board_init(board, width, height);
            board_add_snake(board, start, end);
        } else {
            fprintf(stderr, "⚠️ Unknown line format: %s", line);
        }
    }

    fclose(file);
    return board_initialized;
}
