// g++ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main_value_noise main_value_noise.cpp && ./main_value_noise

#include "value_noise.h"
#include <stdio.h>
#include <raylib.h>

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
      if (map[i][j] < 0.334){
        Color WATER = {0, (unsigned char)(255 * (map[i][j]/0.334)), 255, 255};
          DrawRectangle(j * tile_size, i * tile_size, tile_size, tile_size, WATER);
      }
      else if (map[i][j] < 0.667){
        Color HILL = {0, (unsigned char)(255 - (255 * ((map[i][j] - 0.334)/0.334))), 0, 255};
        DrawRectangle(j * tile_size, i * tile_size, tile_size, tile_size, HILL);
      }
      else{
        Color MOUNTAIN = {(unsigned char)(255 * ((map[i][j] - 0.667)/0.334)), (unsigned char)(255 * ((map[i][j] - 0.667)/0.334)), (unsigned char)(255 * ((map[i][j] - 0.667)/0.334)), 255};
        DrawRectangle(j * tile_size, i * tile_size, tile_size, tile_size, MOUNTAIN);
      }
    }
  }
}

int main(int argc, char * argv[]){
  int seed;
  int oct;
  double scal;
  printf("Input the seed, octave quantinty and the scaling factor: \n");
  scanf("%i %i %lf", &seed, &oct, &scal);

  float ** gmap = generate_value_noise(seed, 1025, oct, scal);
  InitWindow(1024, 1024, "main");
  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(WHITE);
    draw_colors(gmap, 1025, 1);
    EndDrawing();
  }
    
  return 0;
}
