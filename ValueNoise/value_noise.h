#ifndef VALUE_NOISE_H
#define VALUE_NOISE_H

#include "../noise_utils.h"
#include <stdint.h>

float value_noise2D(
    double x, double y, uint64_t seed, uint8_t current_octave,
    ease_function_t ease_function
);

#endif // !VALUE_NOISE_H
