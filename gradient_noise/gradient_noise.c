#include "noise_utils.h"
#include "gradient_noise.h"
#include <stdio.h>
#include <stdlib.h>
#include <xxhash.h>
#include <string.h>
#include <math.h>

float2 generate_unit_vector(size_t y_index, size_t x_index, uint8_t current_octave, uint64_t seed) {
  char * hash_input;
  asprintf(&hash_input, "%lu%lu%hu", y_index, x_index, current_octave);
  uint64_t hash = XXH64(hash_input, strlen(hash_input), seed);
  free(hash_input);
  float2 result = hash_to_unit_vector(hash);
  return result;
}

float4 get_dots(float2 tl, float2 tr, float2 bl, float2 br, float dist_y, float dist_x) {
  float4 dots;
  dots.tl = dot_product(tl, (float2){dist_x, dist_y});
  dots.tr = dot_product(tr, (float2){dist_x - 1, dist_y});
  dots.bl = dot_product(bl, (float2){dist_x, dist_y - 1});
  dots.br = dot_product(br, (float2){dist_x - 1, dist_y - 1});
  return dots;
}

float calculate_gradient_noise(int y, int x, int step_size, uint8_t current_octave, uint64_t seed) {
  int start_y = y - y%step_size;
  int start_x = x - x%step_size;
  int end_y = start_y + step_size;
  int end_x = start_x + step_size;
  float2 tl = generate_unit_vector(start_y, start_x, current_octave, seed);
  float2 tr = generate_unit_vector(start_y, end_x, current_octave, seed);
  float2 bl = generate_unit_vector(end_y, start_x, current_octave, seed);
  float2 br = generate_unit_vector(end_y, end_x, current_octave, seed);
  float dist_y = (y%step_size)/((float)step_size);
  float dist_x = (x%step_size)/((float)step_size);
  float4 dots = get_dots(tl, tr, bl, br, dist_y, dist_x);
  return bicosine_interpolation(dots, dist_y, dist_x);
}

float octave_gradient_noise(int y, int x, int init_step_size, uint8_t octave_count, double persistence, uint64_t seed) {
  float noise = calculate_gradient_noise(y, x, init_step_size, 0, seed);
  for (int o = 1; o < octave_count; o ++) {
    if (init_step_size >> o == 0) break;
    noise += calculate_gradient_noise(y, x, init_step_size >> o, o, seed) * pow(persistence, o);
  }
  return noise;
}
