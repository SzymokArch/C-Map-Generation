#ifndef OUTPUT_H
#define OUTPUT_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} RGB;

int output_to_image(
    float* arr, size_t height, size_t width, char* filename, bool color
);
int output_to_csv(float* arr, size_t height, size_t width, char* filename);

#endif
