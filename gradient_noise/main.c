#include "gradient_noise.h"
#include <string.h>
#include <stdlib.h>

#ifdef RAYLIB_FOUND
    #include <raylib.h>
#else
    #include "raylib/src/raylib.h"
#endif

char get_ASCII(float a) {
    char * buff = "$@B%%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    int size = strlen(buff);
    float b = (a + 1)/2;
    int index = b * (size - 1);
    return buff[index];
}

void draw_greyscale(float ** map, int size, short tile_size){
    Color clr = {0, 0, 0, 255};
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j ++){
            clr.a = (unsigned char)(255 * map[i][j]);
            DrawRectangle(j * tile_size, i * tile_size, tile_size, tile_size, clr);
        }
    }
}

void draw_colors(float ** map, int size, short tile_size){
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j ++){
            float a = (map[i][j] + 1.0f)/2.0f;
            if (a < 0.334){
                Color WATER = {0, (unsigned char)(255 * (a/0.334)), 255, 255};
                DrawRectangle(j * tile_size, i * tile_size, tile_size, tile_size, WATER);
            }
            else if (a < 0.667){
                Color HILL = {0, (unsigned char)(255 - (255 * ((a - 0.334)/0.334))), 0, 255};
                DrawRectangle(j * tile_size, i * tile_size, tile_size, tile_size, HILL);
            }
            else{
                Color MOUNTAIN = {(unsigned char)(255 * ((a - 0.667)/0.334)), (unsigned char)(255 * ((a - 0.667)/0.334)), (unsigned char)(255 * ((a - 0.667)/0.334)), 255};
                DrawRectangle(j * tile_size, i * tile_size, tile_size, tile_size, MOUNTAIN);
            }
        }
    }
}

int main(void) {
    float ** map = calloc(257, sizeof(float *));
    for (int i = 0; i < 257; i ++) {
        map[i] = calloc(257, sizeof(float));
        for (int j = 0; j < 257; j ++) {
            map[i][j] = octave_gradient_noise(i/64., j/64., 6, 0.5, 1337);
        }
    }

    InitWindow(1024, 1024, "Gradient Noise Test");
    while (!(WindowShouldClose())) {
        BeginDrawing(); {
            ClearBackground(WHITE);
            draw_colors(map, 257, 4);
    } EndDrawing();

  }

    for (int i = 0; i < 257; i ++) {
        free(map[i]);
  }
    free(map);
}
