#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gen_aliases.c"

float linear_interpolate(float a, float b, float x){
  return a * (1 - x) + b * x;
}

void interpolate_2D(float ** map, vec2 start, vec2 end){
  for (int i = start.y; i <= end.y; i ++){
    map[i][start.x] = linear_interpolate(map[start.y][start.x], map[end.y][start.x], (double)(i - start.y)/(end.y - start.y));
    map[i][end.x] = linear_interpolate(map[start.y][end.x], map[end.y][end.x], (double)(i - start.y)/(end.y - start.y));
    for (int j = start.x; j < end.x; j ++){
      map[i][j] = linear_interpolate(map[i][start.x], map[i][end.x], (double)(j - start.x)/(end.x - start.x));
    }
  }

}

void init_corner_values(float_map noise_map, float_map target_map, int iteration){
  int pitch = (target_map.height - 1)/pow(2, iteration);
  if (pitch < 1){
    return;
  }
  for (int i = 0; i < target_map.height; i += pitch){
    for (int j = 0; j < target_map.width; j += pitch){
      target_map.map[i][j] = noise_map.map[i][j];
    }
  }
}

void interpolate_between_corners(float_map target_map, int pitch){
  for (int i = 0; i < target_map.height - pitch; i += pitch){
    for (int j = 0; j < target_map.width - pitch; j += pitch){
      interpolate_2D(target_map.map, get_vec2(j, i), get_vec2(j + pitch, i + pitch));
    }
  }
}

// The array dimensions should be equal to 2^n + 1
// Generates a single octave of value noise
float_map value_noise(float_map noise_map, int iteration){
  float_map gen_map;
  gen_map.height = noise_map.height;
  gen_map.width = noise_map.width;
  gen_map.map = (float **)calloc(gen_map.height, sizeof(float *));
  for (int i = 0; i < gen_map.height; i ++){
    gen_map.map[i] = (float *)calloc(gen_map.height, sizeof(float));
  }

  init_corner_values(noise_map, gen_map, iteration);
  int pitch = (gen_map.height - 1)/pow(2, iteration);
  interpolate_between_corners(gen_map, pitch);

  return gen_map;
}

