#include <stdlib.h>
#include <stdbool.h>
#include "cellular_automata.h"

bool is_within_map_bounds(int y, int x, bool ** map, int size){
  if (y < 0 || x < 0 || y >= size || x >= size){
    return false;
  }
  return true;
}

void copy_bool_map(bool ** dest, bool ** src, int size){
  for (int i = 0; i < size; i ++){
    for (int j = 0; j < size; j ++){
      dest[i][j] = src[i][j];
    }
  }
}

void cellular_automata(bool ** map, int size, int iterations){
  int f_count;
  bool ** temp_map = (bool **)calloc(size, sizeof(bool *));
  for (int i = 0; i < size; i ++){
    temp_map[i] = (bool *)calloc(size, sizeof(bool));
  }

  for (int i = 0; i < iterations; i ++){
    copy_bool_map(temp_map, map, size);
    for (int j = 0; j < size; j ++){
      for (int k = 0; k < size; k ++){
        f_count = 0;
        for (int y = j - 1; y <= j + 1; y ++){
          for (int x = k - 1; x <= k + 1; x ++){
            if (is_within_map_bounds(y, x, map, size)){
              if (y != j || x != k){
                if (!temp_map[y][x]){
                  f_count ++;
                }
              }
            }
            else {
              f_count ++;
            }
          }
        }
        if (f_count > 4){
          map[j][k] = 0;
        }
        else {
          map[j][k] = 1;
        }
      }
    }
  }
  for (int i = 0; i < size; i ++){
    free(temp_map[i]);
  }
  free(temp_map);
}

bool ** generate_cellular_automata(int seed, int density, int size, int iterations){
  srand(seed);
  bool ** map = (bool **)calloc(size, sizeof(bool *));
  for (int i = 0; i < size; i ++){
    map[i] = (bool *)calloc(size, sizeof(bool));
    for (int j = 0; j < size; j ++){
      map[i][j] = rand()%101 > density;
    }
  }
  cellular_automata(map, size, iterations);
  return map;
}
