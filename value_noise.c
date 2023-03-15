#include <stdlib.h>
#include <math.h>

// returns a value between a and b
// x is a floating point number between 0 and 1
// x = 0 returns a and x = 1 returns b
float interpolation_cosine(float a, float b, float x){
  float ft = x * M_PI;
  float f = (1 - cos(ft)) * .5;

  return a * (1 - f) + b * f;
}

// function for initializing a square consisting of points gained by interpolating between the (known) corner values
// uses the method for bilinear interpolation but with cosine interpolation instead of linear interpolation
// initializes values on 2 axes (every vertical value for start_x and end_x) and interpolates between them
void interpolation_2D(float ** map, int start_y, int start_x, int end_y, int end_x){
  for (int i = start_y; i <= end_y; i ++){
    map[i][start_x] = interpolation_cosine(map[start_y][start_x], map[end_y][start_x], (double)(i - start_y)/(end_y - start_y));
    map[i][end_x] = interpolation_cosine(map[start_y][end_x], map[end_y][end_x], (double)(i - start_y)/(end_y - start_y));
    for (int j = start_x; j <= end_x; j ++){
      map[i][j] = interpolation_cosine(map[i][start_x], map[i][end_x], (double)(j - start_x)/(end_x - start_x));
    }
  }
}

// sometimes some values in the final generated noise map may be greater than one
// we don't want that, since it makes the map quite inconvenient to display
// this functions takes the generated noise map and normalises the values
// the biggest value found in the map is set to 1 and the smallest to 0
// all other values are asigned accordingly
void normalize_noise(float ** map, int size){
  float maxi = map[0][0];
  float mini = map[0][0];
  for (int i = 0; i < size; i ++){
    for (int j = 0; j < size; j ++){
      if (map[i][j] > maxi){
        maxi = map[i][j];
      }
      if (map[i][j] < mini){
        mini = map[i][j];
      }
    }
  }
  float dif = maxi - mini;
  for (int i = 0; i < size; i ++){
    for (int j = 0; j < size; j ++){
      map[i][j] = (map[i][j] - mini)/dif;
    }
  }
}

// initializes the value noise 2D array
float ** value_noise(float ** noise_map, int size, int octaves, double scaling_factor){
  float ** gen_map = (float **)calloc(size, sizeof(float *));
  for (int i = 0; i < size; i ++){
    gen_map[i] = (float *)calloc(size, sizeof(float));
  }

  int pitch;
  double persistance = 1;

  for (int o = 0; o <= octaves; o ++){
    pitch = (int)(size - 1)/pow(2, o);
    for (int i = 0; i < size; i += pitch){
      for (int j = 0; j < size; j += pitch){
        gen_map[i][j] += noise_map[i][j] * persistance;
      }
    }
    for (int i = 0; i < size - pitch; i += pitch){
      for (int j = 0; j < size - pitch; j += pitch){
        interpolation_2D(gen_map, i, j, i + pitch, j + pitch);
      }
    }
    persistance /= scaling_factor;
  }
  normalize_noise(gen_map, size);
  return gen_map;
}

// generates a square 2D value noise array (the array size has to be equal to 2^n + 1 and the octave count must be <= n)
// couldn't be bothered to implement error handling, so for the love of God input the right values!
float ** generate_value_noise(int seed, int size, int octaves, double scaling_factor){
  srand(seed);
  float ** nmap = (float **)calloc(size, sizeof(float *));
  for (int i = 0; i < size; i ++){
    nmap[i] = (float *)calloc(size, sizeof(float));
    for (int j = 0; j < size; j ++){
      nmap[i][j] = rand()%10001/1000.;
    }
  }
  float ** gmap = value_noise(nmap, size, octaves, scaling_factor);
  for (int i = 0; i < size; i ++){
    free(nmap[i]);
  }
  free(nmap);

  return gmap;
}
