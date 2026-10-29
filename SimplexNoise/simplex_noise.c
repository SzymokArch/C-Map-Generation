#include "../noise_utils.h"
#include "simplex_noise.h"

float simplex_noise2D(
    double x, double y, uint64_t seed, uint8_t current_octave,
    [[maybe_unused]] ease_function_t ease_function
)
{
    double a_contribution, b_contribution, c_contribution;

    // Skew the coordinates into Simplex space
    const double skew_offset = (x + y) * SKEW_FACTOR;
    int a_simplex_x = fastfloor(x + skew_offset);
    int a_simplex_y = fastfloor(y + skew_offset);

    // Unskew back to Cartesian
    const double unskew_offset = (a_simplex_x + a_simplex_y) * UNSKEW_FACTOR;
    double a_cartesian_x = a_simplex_x - unskew_offset;
    double a_cartesian_y = a_simplex_y - unskew_offset;

    double a_displacement_x = x - a_cartesian_x;
    double a_displacement_y = y - a_cartesian_y;

    // B corner
    int b_offset_x, b_offset_y;
    if (a_displacement_x > a_displacement_y) {
        b_offset_x = 1;
        b_offset_y = 0;
    }
    else {
        b_offset_x = 0;
        b_offset_y = 1;
    }
    int b_simplex_x = a_simplex_x + b_offset_x;
    int b_simplex_y = a_simplex_y + b_offset_y;

    double b_displacement_x = a_displacement_x - b_offset_x + UNSKEW_FACTOR;
    double b_displacement_y = a_displacement_y - b_offset_y + UNSKEW_FACTOR;

    // C corner
    int c_simplex_x = a_simplex_x + 1;
    int c_simplex_y = a_simplex_y + 1;

    double c_displacement_x = a_displacement_x - 1.0 + 2.0 * UNSKEW_FACTOR;
    double c_displacement_y = a_displacement_y - 1.0 + 2.0 * UNSKEW_FACTOR;

    // Calculating gradients
    float2 a_gradient
        = get_gradient_at(a_simplex_x, a_simplex_y, seed, current_octave);
    float2 b_gradient
        = get_gradient_at(b_simplex_x, b_simplex_y, seed, current_octave);
    float2 c_gradient
        = get_gradient_at(c_simplex_x, c_simplex_y, seed, current_octave);

    // Calculate contributions
    // A corner contribution
    double a_attenuation = 0.5 - a_displacement_x * a_displacement_x
        - a_displacement_y * a_displacement_y;
    if (a_attenuation < 0.0) {
        a_contribution = 0.0;
    }
    else {
        a_attenuation *= a_attenuation;
        a_contribution = a_attenuation * a_attenuation
            * dot(a_gradient.x,
                  a_gradient.y,
                  a_displacement_x,
                  a_displacement_y);
    }

    // B corner contribution
    double b_attenuation = 0.5 - b_displacement_x * b_displacement_x
        - b_displacement_y * b_displacement_y;
    if (b_attenuation < 0.0) {
        b_contribution = 0.0;
    }
    else {
        b_attenuation *= b_attenuation;
        b_contribution = b_attenuation * b_attenuation
            * dot(b_gradient.x,
                  b_gradient.y,
                  b_displacement_x,
                  b_displacement_y);
    }

    // C corner contribution
    double c_attenuation = 0.5 - c_displacement_x * c_displacement_x
        - c_displacement_y * c_displacement_y;
    if (c_attenuation < 0.0) {
        c_contribution = 0.0;
    }
    else {
        c_attenuation *= c_attenuation;
        c_contribution = c_attenuation * c_attenuation
            * dot(c_gradient.x,
                  c_gradient.y,
                  c_displacement_x,
                  c_displacement_y);
    }

    return 70.0 * (a_contribution + b_contribution + c_contribution);
}

// char get_ASCII(float a)
// {
//     char* buff = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/"
//                  "\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
//     int size = strlen(buff);
//     float b = (a + 1) / 2;
//     int index = b * (size - 1);
//     return buff[index];
// }
//
// int main(int argc, char* argv[])
// {
//     if (argc < 4) {
//         fprintf(stderr, "Invalid argument count!\n");
//     }
//     int size = atoi(argv[1]);
//     int step = atoi(argv[2]);
//     uint64_t seed = atoi(argv[3]);
//     for (int i = 0; i < size; i++) {
//         for (int j = 0; j < size; j++) {
//             double x = (double)j / (double)step;
//             double y = (double)i / (double)step;
//             printf("%c ", get_ASCII(simplex_noise2D(x, y, seed, 0)));
//         }
//         printf("\n");
//     }
//     return 0;
// }
