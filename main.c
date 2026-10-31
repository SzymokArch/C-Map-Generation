
#include "cli/cli.h"
#include "noise.h"
#include "output/output.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* make_filename(const char* prefix, const char* extension)
{
    size_t length = strlen(prefix) + strlen(extension) + 1;

    char* filename = malloc(length);

    if (!filename)
        return NULL;

    snprintf(filename, length, "%s%s", prefix, extension);

    return filename;
}

int main(int argc, char** argv)
{
    cli_config config;

    cli_set_defaults(&config);

    int err = cli_parse(argc, argv, &config);

    if (err == 1) {
        cli_print_help(argv[0]);
        return EXIT_SUCCESS;
    }

    if (err != 0) {
        fprintf(stderr, "Invalid command-line arguments.\n");
        cli_print_help(argv[0]);
        return EXIT_FAILURE;
    }

    size_t pixel_count = config.width * config.height;

    if (pixel_count > SIZE_MAX / sizeof(float)) {
        fprintf(stderr, "Terrain allocation size overflow.\n");
        return EXIT_FAILURE;
    }

    float* terrain = malloc(pixel_count * sizeof(float));

    if (!terrain) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    octave_noise_params params = { .noise_function = config.noise_function,
                                   .x = 0,
                                   .y = 0,
                                   .seed = config.seed,
                                   .octave_count = config.octave_count,
                                   .ease_function = config.ease_function,
                                   .init_cellsize = config.cellsize,
                                   .persistence = config.persistence,
                                   .lacunarity = config.lacunarity };

    printf("Generating terrain: %zux%zu\n", config.width, config.height);

    generate_octave_noise_map(params, terrain, config.height, config.width);

    printf("Generation complete.\n");

    if (config.format == OUTPUT_PNG || config.format == OUTPUT_BOTH) {

        char* filename = make_filename(config.output_name, ".png");

        if (!filename) {
            free(terrain);
            return EXIT_FAILURE;
        }

        err = output_to_image(
            terrain,
            config.height,
            config.width,
            filename,
            config.color
        );

        if (err != 0) {
            fprintf(stderr, "PNG export failed: %s\n", strerror(-err));
        }
        else {
            printf("Saved %s\n", filename);
        }

        free(filename);
    }

    if (config.format == OUTPUT_CSV || config.format == OUTPUT_BOTH) {

        char* filename = make_filename(config.output_name, ".csv");

        if (!filename) {
            free(terrain);
            return EXIT_FAILURE;
        }

        err = output_to_csv(terrain, config.height, config.width, filename);

        if (err != 0) {
            fprintf(stderr, "CSV export failed: %s\n", strerror(-err));
        }
        else {
            printf("Saved %s\n", filename);
        }

        free(filename);
    }

    free(terrain);

    return EXIT_SUCCESS;
}
