#include "dice.h"
#include <stdio.h>

void dice_init(void) {
    // Seed the random number generator with current time
    srand((unsigned int)time(NULL));
}

int dice_roll_uniform(int faces) {
    if (faces <= 0 || faces > MAX_DIE_FACES) {
        fprintf(stderr, "Invalid number of die faces: %d\n", faces);
        return 1;
    }

    return (rand() % faces) + 1;
}

int dice_roll_non_uniform(int faces, const int* probabilities) {
    if (!probabilities || faces <= 0 || faces > MAX_DIE_FACES) {
        return dice_roll_uniform(faces);
    }

    // Calculate total weight
    int total = 0;
    for (int i = 0; i < faces; i++) {
        if (probabilities[i] <= 0) return dice_roll_uniform(faces);
        total += probabilities[i];
    }

    // Generate random number in [1, total]
    int r = (rand() % total) + 1;

    // Find which face corresponds to r
    int cumulative = 0;
    for (int i = 0; i < faces; i++) {
        cumulative += probabilities[i];
        if (r <= cumulative) {
            return i + 1;
        }
    }

    // Fallback (should never happen)
    return faces;
}

bool dice_validate_probabilities(const int* probabilities, int faces) {
    if (!probabilities || faces <= 0 || faces > MAX_DIE_FACES) {
        return false;
    }

    for (int i = 0; i < faces; i++) {
        if (probabilities[i] <= 0) {
            return false;
        }
    }

    return true;
}

