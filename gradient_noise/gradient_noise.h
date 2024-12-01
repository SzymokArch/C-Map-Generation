#ifndef GRADIENT_NOISE_H
#define GRADIENT_NOISE_H
#include "noise_utils.h"
#include <stddef.h>

float2 generate_unit_vector(size_t y_index, size_t x_index, uint8_t current_octave, uint64_t seed);
float4 get_dots(float2 tl, float2 tr, float2 bl, float2 br, float dist_y, float dist_x);
float calculate_gradient_noise(int y, int x, int step_size, uint8_t current_octave, uint64_t seed);
float octave_gradient_noise(int y, int x, int init_step_size, uint8_t octave_count, double persistence, uint64_t seed);

#endif // GRADIENT_NOISE_H