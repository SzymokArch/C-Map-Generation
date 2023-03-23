#ifndef VALUE_NOISE_H
#define VALUE_NOISE_H

float interpolation_cosine(float, float, float);
void interpolation_2D(float **, int, int, int, int);
void normalize_noise(float **, int);
float ** value_noise(float **, int, int, double);
float ** generate_value_noise(int, int, int, double);

#endif // !VALUE_NOISE_H
