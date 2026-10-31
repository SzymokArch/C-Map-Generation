#ifndef NOISE_H
#define NOISE_H

#include "noise_utils.h"
#include <stddef.h>
#include <stdint.h>

typedef float (*noise_function_t)(
    double x, double y, uint64_t seed, uint8_t octave,
    ease_function_t ease_function
);

// NOTE Coordinates are supplied in noise-space fractions, where integers
// traditionally symbolize lattice edges. It is expected of the caller to divide
// a map-space unit by the desired cell size to get the fraction
typedef struct {
    noise_function_t
        noise_function; // gradient_noise, simplex_noise, value_noise
    double x; // noise-space coordinates, integers mean lattice edges
    double y; // noise-space coordinates, integers mean lattice edges
    uint64_t seed; // self-explanatory
    uint8_t current_octave;
    ease_function_t ease_function; // smoothstep, smootherstep, cosine_ease,
                                   // nullptr for no easing. Simplex doesn't use
                                   // easing so the value is ignored
} noise_params;

float noise(noise_params params);

// NOTE Coordinates are supplied in map-space units. They are divided by the
// current cell size internally to obtain fractional noise-space coordinates
typedef struct {
    noise_function_t
        noise_function; // gradient_noise, simplex_noise, value_noise
    int x; // map-space units (e.g. pixels)
    int y; // map-space units (e.g. pixels)
    uint64_t seed; // self-explanatory
    uint8_t octave_count; // if the step gets smaller or equal to 1 then no
                          // further octaves will be calculated
    ease_function_t ease_function; // smoothstep, smootherstep, cosine_ease,
                                   // nullptr for no easing. Simplex doesn't use
                                   // easing so the value is ignored
    double init_cellsize; // the size of the initial lattice cell
    double persistence; // how much amplitude shrinks between octaves
    double lacunarity; // how much frequency grows between octaves
} octave_noise_params;

float octave_noise(octave_noise_params params);

// Flattened 2D array. The caller is expected to allocate and free memory
void generate_noise_map(
    noise_params params, double cellsize, float* arr, size_t height,
    size_t width
);

// Flattened 2D array. The caller is expected to allocate and free memory
void generate_octave_noise_map(
    octave_noise_params params, float* arr, size_t height, size_t width
);

#endif // NOISE_H
