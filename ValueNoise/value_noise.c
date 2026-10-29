#include "../noise_utils.h"
#include "value_noise.h"

float value_noise2D(
    double x, double y, uint64_t seed, uint8_t current_octave,
    ease_function_t ease_function
)
{
    int start_x = fastfloor(x);
    int start_y = fastfloor(y);
    int end_x = start_x + 1;
    int end_y = start_y + 1;

    float tl = get_value_at(start_x, start_y, seed, current_octave);
    float tr = get_value_at(end_x, start_y, seed, current_octave);
    float bl = get_value_at(start_x, end_y, seed, current_octave);
    float br = get_value_at(end_x, end_y, seed, current_octave);

    float dist_y = y - start_y;
    float dist_x = x - start_x;
    if (ease_function != nullptr) {
        dist_y = ease_function(dist_y);
        dist_x = ease_function(dist_x);
    }

    return bilinear_interpolation(tl, tr, bl, br, dist_x, dist_y);
}
