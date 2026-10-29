#include "noise.h"
#include "noise_utils.h"
#include <stdint.h>

float noise(
    noise_function_t noise_function, double x, double y, uint64_t seed,
    uint8_t current_octave, ease_function_t ease_function
)
{
    return noise_function(x, y, seed, current_octave, ease_function);
}
