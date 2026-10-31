
#ifndef CLI_H
#define CLI_H

#include "../noise.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum { OUTPUT_PNG, OUTPUT_CSV, OUTPUT_BOTH } output_format_t;

typedef struct {
    noise_function_t noise_function;

    size_t width;
    size_t height;

    uint64_t seed;
    uint8_t octave_count;

    double persistence;
    double lacunarity;
    double cellsize;

    ease_function_t ease_function;

    output_format_t format;
    bool color;

    const char* output_name;
} cli_config;

void cli_set_defaults(cli_config* config);

int cli_parse(int argc, char** argv, cli_config* config);

void cli_print_help(const char* program_name);

#endif
