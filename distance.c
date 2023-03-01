#include <math.h>
#include <stdlib.h>

typedef struct vec2{
  int x;
  int y;
} vec2;

typedef struct vec3{
  int x;
  int y;
  int z;
} vec3;

// Calculate distance between any 2 points in a 2D space using any type of distance
// I have observed that p > 2 is great for procedural biome map generation using voronoi diagrams
// Kind of slow, if p = 1 or p = 2 use other functions to save on computing speed
float minkowski_distance_2D(vec2 point_a, vec2 point_b, int p){
  return pow(pow(abs(point_a.x - point_a.y), p) + pow(abs(point_b.x - point_b.y), p), 1./p);
}


// Standard distance calculation (minkowski distance p = 2)
float euclid_distance_2D(vec2 point_a, vec2 point_b){
  return sqrt(pow(point_b.y - point_a.y, 2) + pow(point_b.x - point_a.x, 2));
}

// Really fast distance calculation, great for procedural generation of cities using voronoi diagrams
// (minkowski distance p = 1)
float manhattan_distance_2D(vec2 point_a, vec2 point_b){
  return abs(point_b.y - point_a.y) + abs(point_b.x - point_a.x);
}

