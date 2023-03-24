#ifndef VALUE_NOISE_H
#define VALUE_NOISE_H

float interpolation_cosine(float a, float b, float x);
void interpolation_2D(float ** map, int start_y, int start_x, int end_y, int end_x);
void normalize_noise(float ** map, int size);
float ** value_noise(float ** noise_map, int size, int octaves, double scaling_factor);
float ** generate_value_noise(int seed, int size, int octaves, double scaling_factor);

#endif // !VALUE_NOISE_H
