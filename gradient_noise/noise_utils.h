#ifndef NOISE_UTILS_H
#define NOISE_UTILS_H

#define FASTFLOOR(x) ((x) > 0 ? (int)(x) : (int)(x) - 1)
#define CLAMP_ONE(x) ((x) < -1 ? -1 : ((x) > 1 ? 1 : (x)))

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

float dot_product(float2 a, float2 b);
float lin_interpolation(float a, float b, float x);
float bilinear_interpolation(float4 values, float y, float x);
float cos_interpolation(float a, float b, float x);
float bicosine_interpolation(float4 values, float y, float x);

#endif // NOISE_UTILS
