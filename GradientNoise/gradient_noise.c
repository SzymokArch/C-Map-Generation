#include "../noise_utils.h"
#include "gradient_noise.h"

float gradient_noise2D(
    double x, double y, uint64_t seed, uint8_t current_octave,
    ease_function_t ease_function
)
{
    int start_x = fastfloor(x);
    int start_y = fastfloor(y);
    int end_x = start_x + 1;
    int end_y = start_y + 1;

    float2 tl = get_gradient_at(start_x, start_y, seed, current_octave);
    float2 tr = get_gradient_at(end_x, start_y, seed, current_octave);
    float2 bl = get_gradient_at(start_x, end_y, seed, current_octave);
    float2 br = get_gradient_at(end_x, end_y, seed, current_octave);

    float dist_y = y - start_y;
    float dist_x = x - start_x;

    float tl_dot = dot(tl.x, tl.y, dist_x, dist_y);
    float tr_dot = dot(tr.x, tr.y, dist_x - 1, dist_y);
    float bl_dot = dot(bl.x, bl.y, dist_x, dist_y - 1);
    float br_dot = dot(br.x, br.y, dist_x - 1, dist_y - 1);

    if (ease_function != nullptr) {
        dist_y = ease_function(dist_y);
        dist_x = ease_function(dist_x);
    }

    return bilinear_interpolation(
        tl_dot,
        tr_dot,
        bl_dot,
        br_dot,
        dist_x,
        dist_y
    );
}
