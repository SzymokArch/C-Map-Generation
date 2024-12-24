#include "noise_utils.h"
 #include "gradient_noise.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <xxhash.h>
#include <math.h>

#define VECTOR_COUNT 36
float2 VECTORS[36] = 
  {{1.000000, 0.000000}, {0.984808, 0.173648}, {0.939693, 0.342020}, 
  {0.866025, 0.500000}, {0.766044, 0.642788}, {0.642788, 0.766044}, 
  {0.500000, 0.866025}, {0.342020, 0.939693}, {0.173648, 0.984808}, 
  {0.000000, 1.000000}, {-0.173648, 0.984808}, {-0.342020, 0.939693}, 
  {-0.500000, 0.866025}, {-0.642788, 0.766044}, {-0.766044, 0.642788}, 
  {-0.866025, 0.500000}, {-0.939693, 0.342020}, {-0.984808, 0.173648}, 
  {-1.000000, 0.000000}, {-0.984808, -0.173648}, {-0.939693, -0.342020}, 
  {-0.866025, -0.500000}, {-0.766044, -0.642788}, {-0.642788, -0.766044}, 
  {-0.500000, -0.866025}, {-0.342020, -0.939693}, {-0.173648, -0.984808}, 
  {-0.000000, -1.000000}, {0.173648, -0.984808}, {0.342020, -0.939693}, 
  {0.500000, -0.866025}, {0.642788, -0.766044}, {0.766044, -0.642788}, 
  {0.866025, -0.500000}, {0.939693, -0.342020}, {0.984808, -0.173648}};

float2 get_unit_vector(int y_index, int x_index, uint8_t current_octave, uint64_t seed) {
  char * hash_input;
  int hash_seed_len = asprintf(&hash_input, "%i%i%hu", y_index, x_index, current_octave);
  uint64_t hash = XXH64(hash_input, hash_seed_len, seed);
  free(hash_input);
  return VECTORS[hash % VECTOR_COUNT];
}

float4 get_dots(float2 tl, float2 tr, float2 bl, float2 br, float dist_y, float dist_x) {
  float4 dots;
  dots.tl = dot_product(tl, (float2){dist_x, dist_y});
  dots.tr = dot_product(tr, (float2){dist_x - 1, dist_y});
  dots.bl = dot_product(bl, (float2){dist_x, dist_y - 1});
  dots.br = dot_product(br, (float2){dist_x - 1, dist_y - 1});
  return dots;
}

float calculate_gradient_noise(double y, double x, uint8_t current_octave, uint64_t seed) {
  int start_y = FASTFLOOR(y);
  int end_y = start_y + 1;
  int start_x = FASTFLOOR(x);
  int end_x = start_x + 1;
  double dist_y = y - start_y;
  double dist_x = x - start_x;
  float2 tl = get_unit_vector(start_y, start_x, current_octave, seed);
  float2 tr = get_unit_vector(start_y, end_x, current_octave, seed);
  float2 bl = get_unit_vector(end_y, start_x, current_octave, seed);
  float2 br = get_unit_vector(end_y, end_x, current_octave, seed);
  float4 dots = get_dots(tl, tr, bl, br, dist_y, dist_x);
  return bicosine_interpolation(dots, dist_y, dist_x);
}

float octave_gradient_noise(double y, double x, uint8_t octave_count, double persistence, uint64_t seed) {
  float noise = calculate_gradient_noise(y, x, 0, seed);
  for (uint8_t o = 0; o < octave_count; o ++) {
    noise += calculate_gradient_noise(y * (2 << o), x * (2 << o), o, seed) * pow(persistence, o);
    noise = CLAMP_ONE(noise);
  }
  return noise;
}
