#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/stb_image_write.h"
#include "../noise_utils.h"
#include "output.h"

typedef struct {
    float height;
    RGB color;
} color_stop;

static constexpr color_stop TERRAIN_PALETTE[]
    = { { 0.00f, { 18, 59, 102 } },   { 0.20f, { 38, 125, 145 } },
        { 0.30f, { 217, 195, 138 } }, { 0.38f, { 113, 155, 85 } },
        { 0.55f, { 56, 107, 69 } },   { 0.68f, { 155, 149, 102 } },
        { 0.82f, { 130, 125, 120 } }, { 0.93f, { 190, 190, 185 } },
        { 1.00f, { 232, 233, 229 } } };

static constexpr size_t PALETTE_SIZE
    = sizeof(TERRAIN_PALETTE) / sizeof(TERRAIN_PALETTE[0]);

// expected values remapped to [0, 1]
static RGB get_color_from_height(float height)
{
    height = clamp01(height);

    for (size_t i = 0; i < PALETTE_SIZE - 1; i++) {
        if (height <= TERRAIN_PALETTE[i + 1].height) {
            float t = (height - TERRAIN_PALETTE[i].height)
                / (TERRAIN_PALETTE[i + 1].height - TERRAIN_PALETTE[i].height);

            RGB a = TERRAIN_PALETTE[i].color;
            RGB b = TERRAIN_PALETTE[i + 1].color;

            RGB result = { .r = (uint8_t)lerp(a.r, b.r, t),
                           .g = (uint8_t)lerp(a.g, b.g, t),
                           .b = (uint8_t)lerp(a.b, b.b, t) };

            return result;
        }
    }

    return TERRAIN_PALETTE[PALETTE_SIZE - 1].color;
}

// expected values remapped to [0, 1]
static uint8_t get_greyscale(float value)
{
    return (uint8_t)(value * 255.0f);
}

int output_to_image(
    float* arr, size_t height, size_t width, char* filename, bool color
)
{
    if (!arr || !filename)
        return -EINVAL;

    if (width == 0 || height == 0)
        return -EINVAL;

    if (width > SIZE_MAX / height)
        return -EOVERFLOW;

    size_t pixel_count = width * height;
    int channels = color ? 3 : 1;

    if (pixel_count > SIZE_MAX / (size_t)channels)
        return -EOVERFLOW;

    if (width > INT_MAX / channels || height > INT_MAX)
        return -EOVERFLOW;

    uint8_t* pixels = calloc(pixel_count * channels, 1);

    if (!pixels)
        return -ENOMEM;

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            size_t index = i * width + j;

            float value = clamp01(remap_signed_to_01(arr[index]));

            if (color) {
                RGB clr = get_color_from_height(value);

                pixels[index * 3] = clr.r;
                pixels[index * 3 + 1] = clr.g;
                pixels[index * 3 + 2] = clr.b;
            }
            else {
                pixels[index] = get_greyscale(value);
            }
        }
    }

    int result = stbi_write_png(
        filename,
        (int)width,
        (int)height,
        channels,
        pixels,
        (int)(width * channels)
    );

    free(pixels);

    if (!result)
        return -EIO;

    return EXIT_SUCCESS;
}

int output_to_csv(float* arr, size_t height, size_t width, char* filename)
{
    if (!arr || !filename || width == 0 || height == 0)
        return -EINVAL;

    if (width > SIZE_MAX / height)
        return -EOVERFLOW;

    FILE* file = fopen(filename, "w");

    if (!file) {
        return -errno;
    }

    int err = 0;

    if (fprintf(
            file,
            "# Procedural Noise Map\n"
            "# format_version=1\n"
            "# width=%zu\n"
            "# height=%zu\n"
            "# data_type=float32\n"
            "# data\n",
            width,
            height
        )
        < 0) {
        err = errno;
    }

    for (size_t i = 0; i < height && err == 0; i++) {
        for (size_t j = 0; j < width; j++) {
            if (fprintf(file, "%.9g", (double)arr[i * width + j]) < 0) {
                err = errno;
                break;
            }

            if (j + 1 < width) {
                if (fputc(',', file) == EOF) {
                    err = errno;
                    break;
                }
            }
        }

        if (err != 0) {
            break;
        }

        if (fputc('\n', file) == EOF) {
            err = errno;
        }
    }

    if (fclose(file) == EOF && err == 0) {
        err = errno;
    }

    if (err != 0) {
        return -EIO;
    }

    return 0;
}
