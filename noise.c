#include "noise.h"
#include "noise_utils.h"
#include <stdint.h>

float noise(noise_params params)
{
    return params.noise_function(
        params.x,
        params.y,
        params.seed,
        params.current_octave,
        params.ease_function
    );
}

float octave_noise(octave_noise_params params)
{
    double step = params.init_cellsize;
    double amplitude = 1.0;
    float noise_val = 0.0f;
    uint8_t current_octave = 0;
    while (step > 1 && current_octave < params.octave_count) {
        noise_val += params.noise_function(
                         params.x / step,
                         params.y / step,
                         params.seed,
                         current_octave,
                         params.ease_function
                     )
            * amplitude;

        current_octave += 1;
        amplitude *= params.persistence;
        step /= params.lacunarity;
    }
    return clamp_signed_unit(noise_val);
}

void generate_noise_map(
    noise_params params, double cellsize, float* arr, size_t height,
    size_t width
)
{
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            params.x = j / cellsize;
            params.y = i / cellsize;
            arr[i * width + j] = noise(params);
        }
    }
}

void generate_octave_noise_map(
    octave_noise_params params, float* arr, size_t height, size_t width
)
{
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            params.x = j;
            params.y = i;
            arr[i * width + j] = octave_noise(params);
        }
    }
}
