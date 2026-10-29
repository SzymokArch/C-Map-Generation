#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void gen_gradient_array(uint8_t n)
{
    printf("static constexpr int GRADIENT_COUNT = %hu;\n", n);
    printf("static constexpr float2 GRADIENTS[%hu] = {\n", n);
    const double CIRCLE_LEN = 2 * 3.1415927f;
    for (int i = 0; i < n; i++) {
        double frac = (double)i / (double)n;
        double angle = CIRCLE_LEN * frac;
        double x = cos(angle);
        double y = sin(angle);
        printf("\t{ %.9ff, %.9ff }", x, y);
        if (i < n - 1) {
            printf(",\n");
        }
        else {
            printf("\n");
        }
    }
    printf("};\n");
}

double gen_skew_factor(uint8_t n)
{
    return (sqrt((float)n + 1.0f) - 1.0f) / (float)n;
}

double gen_unskew_factor(uint8_t n)
{
    return (1.0f - 1.0f / sqrt((float)n + 1.0f)) / (float)n;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Arguments not given!\n");
        return 1;
    }
    int gradient_count = atoi(argv[1]);
    gen_gradient_array(gradient_count);

    int dimension_count = atoi(argv[2]);
    printf(
        "static constexpr double SKEW_FACTOR = %.24lf;\n",
        gen_skew_factor(dimension_count)
    );
    printf(
        "static constexpr double UNSKEW_FACTOR = %.24lf;\n",
        gen_unskew_factor(dimension_count)
    );
    return 0;
}
