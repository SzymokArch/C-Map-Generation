#ifndef SIMPLEX_NOISE_H
#define SIMPLEX_NOISE_H

#include "../noise_utils.h"
#include <stdint.h>

float simplex_noise2D(
    double x, double y, uint64_t seed, uint8_t current_octave,
    [[maybe_unused]] ease_function_t ease_function
);

#endif // !SIMPLEX_NOISE_H
