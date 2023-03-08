#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gen_aliases.c"

float linear_interpolate(float a, float b, float x){
  return a * (1 - x) + b * x;
}

void interpolate_2D(float ** map, int start_y, int start_x, int end_y, int end_x, short type){
  for (int i = 0; i <= end_y; i ++){
    map[i][0] = linear_interpolate(map[start_y][start_x], map[end_y][start_x], (double)i/(end_y));
    map[i][end_x] = linear_interpolate(map[start_y][end_x], map[end_y][end_x], (double)i/(end_y));
    for (int j = 0; j < end_x; j ++){
      map[i][j] = linear_interpolate(map[i][start_x], map[i][end_x], (double)j/(end_x));
    }
  }

}

// The array dimensions should be equal to 2^n + 1
float_map value_noise(float_map noise_map, int octaves, double persistence){
  float_map gen_map;
  gen_map.height = noise_map.height;
  gen_map.width = noise_map.width;
  gen_map.map = (float **)calloc(gen_map.height, sizeof(float *));
  for (int i = 0; i < gen_map.height; i ++){
      gen_map.map[i] = (float *)calloc(gen_map.height, sizeof(float));
  }

  double p = 1;
  int temp_y;
  int temp_x;
  for (int o = 0; o < octaves; o ++){
    temp_y = (int)(gen_map.height - 1)/pow(2, o);
    temp_x = (int)(gen_map.width - 1)/pow(2, o);
    if (temp_y < 1 || temp_x < 1){
        break;
    }
    for (int i = 0; i < gen_map.height; i += temp_y){
      for (int j = 0; j < gen_map.width; j += temp_x){
        gen_map.map[i][j] = gen_map.map[i][j] + (noise_map.map[i][j] / p);
      }
    }
    for (int i = 0; i < gen_map.height - temp_y; i += temp_y){
      for (int j = 0; j < gen_map.width - temp_x; j += temp_x){
        interpolate_2D(gen_map.map, i, j, i + temp_y, j + temp_x, 1);
      }
    }
      p /= persistence;
  }

  return gen_map;
}
