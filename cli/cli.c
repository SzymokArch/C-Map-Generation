
#include "cli.h"

#include "../GradientNoise/gradient_noise.h"
#include "../SimplexNoise/simplex_noise.h"
#include "../ValueNoise/value_noise.h"

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cli_set_defaults(cli_config* config)
{
    *config = (cli_config) { .noise_function = gradient_noise2D,
                             .width = 1024,
                             .height = 1024,
                             .seed = 12345,
                             .octave_count = 6,
                             .persistence = 0.5,
                             .lacunarity = 2.0,
                             .cellsize = 128.0,
                             .ease_function = smootherstep,
                             .format = OUTPUT_PNG,
                             .color = false,
                             .output_name = "terrain" };
}

void cli_print_help(const char* program_name)
{
    printf(
        "Usage: %s [OPTIONS]\n\n"
        "Noise generation:\n"
        "  --noise NAME         gradient, simplex, value\n"
        "  --seed N             Random seed\n"
        "  --octaves N          Number of octaves\n"
        "  --persistence N      Amplitude multiplier\n"
        "  --lacunarity N       Frequency multiplier\n"
        "  --cellsize N         Initial cell size\n"
        "  --easing NAME        smoothstep, smootherstep,\n"
        "                       cosine, none\n\n"
        "Map dimensions:\n"
        "  --width N            Map width\n"
        "  --height N           Map height\n\n"
        "Output:\n"
        "  --format NAME        png, csv, both\n"
        "  --color              Use terrain color palette\n"
        "  --no-color           Use greyscale\n"
        "  --output NAME        Output filename prefix\n\n"
        "General:\n"
        "  -h, --help           Display this help message\n",
        program_name
    );
}

static const char* next_value(int argc, char** argv, int* index)
{
    if (*index + 1 >= argc) {
        return NULL;
    }

    (*index)++;
    return argv[*index];
}

static bool parse_size(const char* str, size_t* result)
{
    if (!str || str[0] == '-')
        return false;

    errno = 0;
    char* end;

    unsigned long long value = strtoull(str, &end, 10);

    if (errno == ERANGE || *str == '\0' || *end != '\0') {
        return false;
    }

    if (value > SIZE_MAX) {
        return false;
    }

    *result = (size_t)value;
    return true;
}

static bool parse_u64(const char* str, uint64_t* result)
{
    if (!str || str[0] == '-') {
        return false;
    }

    errno = 0;
    char* end;

    unsigned long long value = strtoull(str, &end, 10);

    if (errno == ERANGE || *str == '\0' || *end != '\0') {
        return false;
    }

    if (value > UINT64_MAX) {
        return false;
    }

    *result = (uint64_t)value;
    return true;
}

static bool parse_double(const char* str, double* result)
{
    if (!str) {
        return false;
    }

    errno = 0;
    char* end;

    double value = strtod(str, &end);

    if (errno == ERANGE || *str == '\0' || *end != '\0')
        return false;

    if (!isfinite(value))
        return false;

    *result = value;
    return true;
}

int cli_parse(int argc, char** argv, cli_config* config)
{
    if (!config) {
        return -EINVAL;
    }

    for (int i = 1; i < argc; i++) {
        const char* arg = argv[i];
        const char* value;

        if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
            return 1;
        }

        if (strcmp(arg, "--color") == 0) {
            config->color = true;
            continue;
        }

        if (strcmp(arg, "--no-color") == 0) {
            config->color = false;
            continue;
        }

        value = next_value(argc, argv, &i);

        if (!value) {
            return -EINVAL;
        }

        if (strcmp(arg, "--noise") == 0) {
            if (strcmp(value, "gradient") == 0) {
                config->noise_function = gradient_noise2D;
            }
            else if (strcmp(value, "simplex") == 0) {
                config->noise_function = simplex_noise2D;
            }
            else if (strcmp(value, "value") == 0) {
                config->noise_function = value_noise2D;
            }
            else {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--width") == 0) {
            if (!parse_size(value, &config->width)) {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--height") == 0) {
            if (!parse_size(value, &config->height)) {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--seed") == 0) {
            if (!parse_u64(value, &config->seed)) {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--octaves") == 0) {
            size_t octaves;

            if (!parse_size(value, &octaves)) {
                return -EINVAL;
            }

            if (octaves > UINT8_MAX) {
                return -ERANGE;
            }

            config->octave_count = (uint8_t)octaves;
        }

        else if (strcmp(arg, "--persistence") == 0) {
            if (!parse_double(value, &config->persistence)) {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--lacunarity") == 0) {
            if (!parse_double(value, &config->lacunarity)) {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--cellsize") == 0) {
            if (!parse_double(value, &config->cellsize)) {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--easing") == 0) {
            if (strcmp(value, "smoothstep") == 0) {
                config->ease_function = smoothstep;
            }
            else if (strcmp(value, "smootherstep") == 0) {
                config->ease_function = smootherstep;
            }
            else if (strcmp(value, "cosine") == 0) {
                config->ease_function = cosine_ease;
            }
            else if (strcmp(value, "none") == 0) {
                config->ease_function = nullptr;
            }
            else {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--format") == 0) {
            if (strcmp(value, "png") == 0) {
                config->format = OUTPUT_PNG;
            }
            else if (strcmp(value, "csv") == 0) {
                config->format = OUTPUT_CSV;
            }
            else if (strcmp(value, "both") == 0) {
                config->format = OUTPUT_BOTH;
            }
            else {
                return -EINVAL;
            }
        }

        else if (strcmp(arg, "--output") == 0) {
            config->output_name = value;
        }

        else {
            return -EINVAL;
        }
    }

    // Validate configuration

    if (config->width == 0 || config->height == 0) {
        return -EINVAL;
    }

    if (config->width > SIZE_MAX / config->height) {
        return -EOVERFLOW;
    }

    if (config->cellsize <= 0.0) {
        return -EINVAL;
    }

    if (config->lacunarity <= 1.0) {
        return -EINVAL;
    }

    if (config->persistence < 0.0) {
        return -EINVAL;
    }

    if (config->format != OUTPUT_CSV) {
        if (config->width > INT_MAX || config->height > INT_MAX) {
            return -EOVERFLOW;
        }

        if (config->color && config->width > INT_MAX / 3) {
            return -EOVERFLOW;
        }
    }

    return 0;
}
