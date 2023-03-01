#include <stdlib.h>
#include "distance.c"

int get_closest_gen(vec2 * generators, int generator_quantity, vec2 point, int p){
  float * distances = (float *)calloc(generator_quantity, sizeof(float));
  
  float min = distances[0];
  int min_index = 0;

  switch (p){
    // manhattan (taxicab) distance (minkowski distance, p = 1)
    case 1:
      for (int i = 0; i < generator_quantity; i ++){
        distances[i] = manhattan_distance_2D(point, generators[i]);
      }
      break;
    // euclidean distance (minkowski distance, p = 2)
    case 2:
      for (int i = 0; i < generator_quantity; i ++){
        distances[i] = euclid_distance_2D(point, generators[i]);
      }
      break;
    // any other minkowski distance p
    default:
      for (int i = 0; i < generator_quantity; i ++){
        distances[i] = minkowski_distance_2D(point, generators[i], p);
      }
      break;
  }

  for (int i = 0; i < generator_quantity; i ++){
    if (distances[i] < min){
      min = distances[i];
      min_index = i;
    }
  }
  free(distances);
  return min_index;
}

// The algorithm uses an extremely slow aproach to calculating distance, (checking every generator with every point in the array)
// I don't really understand fortune's algorithm, and it is only used to generate a diagram with euclidean distance
// TODO Implement fortune's algorithm to generate the diagram when p = 2 (euclidean distance)
int ** generate_voronoi_diagram(vec2 * generators, int generator_quantity, int height, int width, int p){
  int ** diagram = (int **)calloc(height, sizeof(int *));
  for (int i = 0; i < height; i ++){
    diagram[i] = (int *)calloc(width, sizeof(int));
    for (int j = 0; j < width; j ++){
      diagram[i][j] = get_closest_gen(generators, generator_quantity, get_vec2(j, i), p);
    }
  }
  return diagram;
}
