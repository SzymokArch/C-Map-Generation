#ifndef NOISE_UTILS_H
#define NOISE_UTILS_H
#include <stdint.h>

typedef struct float2 {
  float x;
  float y;
} float2;

typedef struct float4 {
  float tl;
  float tr;
  float bl;
  float br;
} float4;

typedef enum DIRECTION {
  UP_LEFT = 0, 
  UP_RIGHT = 1, 
  DOWN_LEFT = 2, 
  DOWN_RIGHT = 3
} DIRECTION;

float dot_product(float2 a, float2 b);
float hash_to_normalized_float(uint64_t hash);
float2 hash_to_unit_vector(uint64_t hash);
float lin_interpolation(float a, float b, float x);
float bilinear_interpolation(float4 values, float y, float x);
float cos_interpolation(float a, float b, float x);
float bicosine_interpolation(float4 values, float y, float x);


#endif // NOISE_UTILS
