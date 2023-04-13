#include "voronoi.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char * argv[]){
  Color clr = {0, 0, 0, 255};
  int seed, p, size;
  size = 513;
  printf("Input the seed and the p factor: \n");
  scanf("%i %i", &seed, &p);
  //short ** diagram = generate_voronoi_diagram(seed, 1025, 4, p);
  float ** map = generate_worley_noise(seed, size, 3, p);
  InitWindow(1024, 1024, "voronoi diagram example");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    for (int i = 0; i < size; i ++){
      for (int j = 0; j < size; j ++){
        //clr.g = (unsigned char)((diagram[i][j]/pow(4, 2)) * 255);
        //DrawRectangle(j * 16, i * 16, 16, 16, clr);
        clr.a = (unsigned char)(map[i][j] * 255);
        DrawRectangle(j * 2, i * 2, 2, 2, clr);
      }
    }
    EndDrawing();
  }
  return 0;
}
