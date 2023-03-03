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

typedef struct int_map{
    int height;
    int width;
    int ** map;
} int_map;