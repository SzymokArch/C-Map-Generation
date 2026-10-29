#ifndef NOISE_UTILS_H
#define NOISE_UTILS_H

#include <math.h>
#include <stdint.h>

typedef struct {
    float x;
    float y;
} float2;
static constexpr int GRADIENT_COUNT = 16;

static constexpr double SKEW_FACTOR = 0.366025403784438596588302;
static constexpr double UNSKEW_FACTOR = 0.211324865405187078959415;

static inline int fastfloor(double x)
{
    int i = (int)x;
    return x < (double)i ? i - 1 : i;
}

static inline double dot(double x0, double y0, double x1, double y1)
{
    return x0 * x1 + y0 * y1;
}

static inline float lerp(float a, float b, float x)
{
    return fmaf(b - a, x, a);
}

static inline float clamp01(float x)
{
    return fminf(fmaxf(x, 0.0f), 1.0f);
}

static inline float remap_signed_to_01(float x)
{
    return (x + 1.0f) * 0.5f;
}

typedef float (*ease_function_t)(float x);

static inline float smoothstep(float x)
{
    return x * x * (3.0f - 2.0f * x);
}

static inline float smootherstep(float x)
{

    return x * x * x * (x * (6.0f * x - 15.0f) + 10.0f);
}

static inline float cosine_ease(float x)
{
    return (1 - cosf(x * 3.1415927f)) * 0.5;
}

float2 get_gradient_at(int x, int y, uint64_t seed, uint8_t current_octave);
float get_value_at(int x, int y, uint64_t seed, uint8_t current_octave);
float bilinear_interpolation(
    float tl, float tr, float bl, float br, float x, float y
);

#endif // NOISE_UTILS_H
