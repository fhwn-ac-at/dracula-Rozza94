#pragma once

#include <stdlib.h>  // for rand()
#include <time.h>    // for seeding
#include <stdbool.h>

#define MAX_DIE_FACES 20  // أقصى عدد أوجه للنرد المدعوم

/**
 * Initializes the random number generator.
 * Call once at program startup.
 */
void dice_init(void);

/**
 * Rolls a fair die with the given number of faces.
 * @param faces Number of die faces (e.g., 6).
 * @return A value between 1 and faces.
 */
int dice_roll_uniform(int faces);

/**
 * Rolls a non-uniform die with weighted probabilities.
 * @param faces Number of die faces.
 * @param probabilities Array of positive integers representing weights for each face.
 *                      Must have exactly `faces` entries.
 * @return A value between 1 and faces, based on weighted probability.
 */
int dice_roll_non_uniform(int faces, const int* probabilities);

/**
 * Validates the probability array for non-uniform die.
 * @param probabilities Array of probabilities.
 * @param faces Number of faces.
 * @return true if valid (all values > 0), false if invalid.
 */
bool dice_validate_probabilities(const int* probabilities, int faces);

