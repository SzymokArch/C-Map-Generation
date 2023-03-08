#include <stdbool.h>
#include <stdlib.h>

typedef struct vec2{
    int x;
    int y;
} vec2;

vec2 get_vec2(int x, int y){
    vec2 result;
    result.x = x;
    result.y = y;
    return result;
}

typedef struct bool_map{
    int height;
    int width;
    bool ** map;
} bool_map;

void copy_bool_map(bool_map src, bool_map dest){
    for (int i = 0; i < src.height; i ++){
        for (int j = 0; j < src.width; j ++){
            dest.map[i][j] = src.map[i][j];
        }
    }
}

void free_bool_map(bool_map mp){
  for (int i = 0; i < mp.height; i ++){
    free(mp.map[i]);
  }
  free(mp.map);
  mp.height = 0;
  mp.width = 0;
}

typedef struct short_map{
    int height;
    int width;
    short ** map;
} short_map;

void copy_short_map(short_map src, short_map dest){
    for (int i = 0; i < src.height; i ++){
        for (int j = 0; j < src.width; j ++){
            dest.map[i][j] = src.map[i][j];
        }
    }
}

void free_short_map(short_map mp){
  for (int i = 0; i < mp.height; i ++){
    free(mp.map[i]);
  }
  free(mp.map);
  mp.height = 0;
  mp.width = 0;
}

typedef struct float_map{
    int height;
    int width;
    float ** map;
} float_map;

void copy_float_map(float_map src, float_map dest){
    for (int i = 0; i < src.height; i ++){
        for (int j = 0; j < src.width; j ++){
            dest.map[i][j] = src.map[i][j];
        }
    }
}

void free_float_map(float_map mp){
  for (int i = 0; i < mp.height; i ++){
    free(mp.map[i]);
  }
  free(mp.map);
  mp.height = 0;
  mp.width = 0;
}
