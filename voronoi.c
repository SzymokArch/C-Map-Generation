#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct site{
  int y;
  int x;
} site;

float minkowski_distance(int ay, int ax, int by, int bx, int p){
  switch (p){
    case 1:
      return abs(by - ay) + abs(bx - ax);
    case 2:
      return sqrt(pow(by - ay, 2) + pow(bx - ax, 2));
    default:
      return pow(pow(abs(ay - by), p) + pow(abs(ax - bx), p), 1./p);
  }
}

site get_center(int start_y, int start_x, int pitch){
  site result;
  result.y = abs(2 * start_y + pitch) / 2;
  result.x = abs(2 * start_x + pitch) / 2;
  return result;
}

site * get_center_array(int size, int divisions){
  site * center_array = (site *)calloc(pow(4, divisions), sizeof(site));
  int pitch = (size - 1)/pow(2, divisions);
  int index = 0;
  for (int i = 0; i < size - pitch; i += pitch){
    for (int j = 0; j < size - pitch; j += pitch){
      center_array[index].y = (2 * i + pitch)/2;
      center_array[index].x = (2 * j + pitch)/2;
      index ++;
    }
  }
  return center_array;
}

void move_centers(int seed, site * center_array, int center_quantity){
  srand(seed);
  bool movement_down;
  bool movement_right;
  int max_movement = center_array[0].x;
  for (int i = 0; i < center_quantity; i ++){
    movement_down = rand()%101 > 50;
    movement_right = rand()%101 > 50;
    if (movement_down){
      center_array[i].y += rand()%max_movement;
    }
    else{
      center_array[i].y -= rand()%max_movement;
    }
    if (movement_right){
      center_array[i].x += rand()%max_movement;
    }
    else{
      center_array[i].x -= rand()%max_movement;
    }
  }
}

short get_closest_site(int y, int x, site * sites, int site_quantity, int p){
  float min;
  short index;
  float * distances = (float *)calloc(site_quantity, sizeof(float));
  min = minkowski_distance(y, x, sites[0].y, sites[0].x, p);
  index = 0;
  for (int i = 0; i < site_quantity; i++){
    distances[i] = minkowski_distance(y, x, sites[i].y, sites[i].x, p);
    if (distances[i] < min){
      min = distances[i];
      index = i;
    }
  }
  return index;
}

void voronoi_diagram(short ** map, int size, site * sites, int site_quantity, int p){
  for (int i = 0; i < size; i ++){
    for (int j = 0; j < size; j ++){
      map[i][j] = get_closest_site(j, i, sites, site_quantity, p);
    }
  }
}

short ** generate_voronoi_diagram(int seed, int size, int divisions, int p){
  srand(seed);
  short ** map = (short **)calloc(size, sizeof(short *));
  for (int i = 0; i < size; i ++){
    map[i] = (short *)calloc(size, sizeof(short));
  }
  site * centarr = get_center_array(size, divisions);
  int cent_q = pow(4, divisions);
  move_centers(seed, centarr, cent_q);
  voronoi_diagram(map, size, centarr, cent_q, p);

  free(centarr);
  return map;
}

//int main(int argc, char * argv[]){
//  short ** map = generate_voronoi_diagram(2133, 33, 2, 3);
//  for (int i = 0; i < 33; i ++){
//    for (int j = 0; j < 33; j ++){
//     printf("%i ", map[i][j]);
//    }
//    printf("\n");
//  }
//
//  for (int i = 0; i < 33; i ++){
//    free(map[i]);
//  }
//  free(map);
//  return 0;
//}
