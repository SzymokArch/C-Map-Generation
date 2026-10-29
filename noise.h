#ifndef NOISE_H
#define NOISE_H

#include "noise_utils.h"
#include <stdint.h>

typedef float (*noise_function_t)(
    double x, double y, uint64_t seed, uint8_t octave,
    ease_function_t ease_function
);

float noise(
    noise_function_t noise_function, double x, double y, uint64_t seed,
    uint8_t current_octave, ease_function_t ease_function
);

float octave_noise(
    noise_function_t noise_function, double x, double y, uint64_t seed,
    uint8_t octave_count, double persistence, double lacunarity
);

#endif
