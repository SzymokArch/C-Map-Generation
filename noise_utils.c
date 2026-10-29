#include "noise_utils.h"
#include <stddef.h>

static constexpr float2 GRADIENTS[GRADIENT_COUNT]
    = { { 1.000000000f, 0.000000000f },   { 0.923879533f, 0.382683432f },
        { 0.707106781f, 0.707106781f },   { 0.382683432f, 0.923879533f },
        { 0.000000000f, 1.000000000f },   { -0.382683432f, 0.923879533f },
        { -0.707106781f, 0.707106781f },  { -0.923879533f, 0.382683432f },
        { -1.000000000f, 0.000000000f },  { -0.923879533f, -0.382683432f },
        { -0.707106781f, -0.707106781f }, { -0.382683432f, -0.923879533f },
        { -0.000000000f, -1.000000000f }, { 0.382683432f, -0.923879533f },
        { 0.707106781f, -0.707106781f },  { 0.923879533f, -0.382683432f } };

float2 get_gradient_at(int x, int y, uint64_t seed, uint8_t current_octave)
{
    // Mix the seed with the current octave
    seed += UINT64_C(0x9e3779b97f4a7c15) * ((uint64_t)current_octave + 1);
    seed = (seed ^ (seed >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    seed = (seed ^ (seed >> 27)) * UINT64_C(0x94d049bb133111eb);
    seed ^= (seed >> 31);

    // Hash the input values
    uint64_t combined = ((uint64_t)(uint32_t)x << 32) | (uint32_t)y;
    uint64_t hash = combined ^ seed;
    hash = (hash ^ (hash >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    hash = (hash ^ (hash >> 27)) * UINT64_C(0x94d049bb133111eb);
    hash ^= (hash >> 31);

    // Mask the hash to get the gradient from the array
    size_t index = hash & (GRADIENT_COUNT - 1);
    return GRADIENTS[index];
}

float get_value_at(int x, int y, uint64_t seed, uint8_t current_octave)
{
    // Mix the seed with the current octave
    seed += UINT64_C(0x9e3779b97f4a7c15) * ((uint64_t)current_octave + 1);
    seed = (seed ^ (seed >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    seed = (seed ^ (seed >> 27)) * UINT64_C(0x94d049bb133111eb);
    seed ^= (seed >> 31);

    // Hash the input values
    uint64_t combined = ((uint64_t)(uint32_t)x << 32) | (uint32_t)y;
    uint64_t hash = combined ^ seed;
    hash = (hash ^ (hash >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    hash = (hash ^ (hash >> 27)) * UINT64_C(0x94d049bb133111eb);
    hash ^= (hash >> 31);

    // Convert the upper 24 bits to [0, 1).
    return (float)(hash >> 40) * (1.0f / 16777216.0f);
}

float bilinear_interpolation(
    float tl, float tr, float bl, float br, float x, float y
)
{
    float a = lerp(tl, bl, y);
    float b = lerp(tr, br, y);
    return lerp(a, b, x);
}
