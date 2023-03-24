#include "cellular_automata.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void draw_greyscale(bool ** map, int size){
  for (int i = 0; i < size; i ++){
    for (int j = 0; j < size; j ++){
      Color clr = {(unsigned char)(255 * map[i][j]), (unsigned char)(255 * map[i][j]), (unsigned char)(255 * map[i][j]), 255};
      DrawRectangle(j * 8, i * 8, 8, 8, clr);
    }
  }
}

int main(int argc, char * argv[]){
  int seed;
  int density;
  int iterations;
  printf("Input the seed, density and iteration quantity: \n");
  scanf("%i %i %i", &seed, &density, &iterations);
  bool ** gmap = generate_cellular_automata(seed, density, 129, iterations);

  InitWindow(1024, 1024, "cellular automata example");
  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(WHITE);
    draw_greyscale(gmap, 129);
    EndDrawing();
  }
  

  return 0;
}
