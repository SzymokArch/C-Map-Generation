#include "voronoi.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char * argv[]){
  Color clr = {0, 0, 0, 255};
  int seed, p;
  printf("Input the seed and the p factor: \n");
  scanf("%i %i", &seed, &p);
  short ** diagram = generate_voronoi_diagram(seed, 65, 2, p);
  InitWindow(1024, 1024, "voronoi diagram example");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    for (int i = 0; i < 65; i ++){
      for (int j = 0; j < 65; j ++){
        clr.g = (unsigned char)((diagram[i][j]/pow(4, 2)) * 255);
        DrawRectangle(j * 16, i * 16, 16, 16, clr);
      }
    }
    EndDrawing();
  }
  return 0;
}
