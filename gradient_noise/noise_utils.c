#include "noise_utils.h"
#include <math.h>
#include <limits.h>

float dot_product(float2 a, float2 b) {
    return a.x * b.x + a.y * b.y;
}

float lin_interpolation(float a, float b, float x) {
    return a * (1 - x) + b * x;
}

float bilinear_interpolation(float4 values, float y, float x) {
    float a = lin_interpolation(values.tl, values.bl, y);
    float b = lin_interpolation(values.tr, values.br, y);
    return lin_interpolation(a, b, x);
}

float cos_interpolation(float a, float b, float x) {
    float ft = x * 3.1415927;
    float f = (1 - cos(ft)) * 0.5;
    return a * (1 - f) + b * f;
}

float bicosine_interpolation(float4 values, float y, float x) {
    float a = cos_interpolation(values.tl, values.bl, y);
    float b = cos_interpolation(values.tr, values.br, y);
    return cos_interpolation(a, b, x);
}
