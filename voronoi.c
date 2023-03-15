#include <stdlib.h>
#include "distance.c"

vec2 get_center(vec2 start, vec2 end){
  int x = abs(end.x - start.x)/2;
  int y = abs(end.y - start.y)/2;
  return get_vec2(x, y);
}

vec2 * get_center_array(short_map map, short iterations){
  int center_quantity = pow(4, iterations);
  vec2 * center_array = (vec2 *)calloc(center_quantity, sizeof(vec2));
  int pitch = (map.height - 1)/pow(2, iterations);
  short index = 0;
  for (int i = 0; i < map.height - pitch; i += pitch){
    for (int j = 0; j < map.width - pitch; j += pitch){
      center_array[index] = get_center(get_vec2(j, i), get_vec2(j + pitch, i + pitch));
      index ++;
    }
  }
  return center_array;
}

void move_centers(int seed, vec2 * center_array, int center_quantity){
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

// gives the index of the closest generator to the given point
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
// I don't really understand fortune's algorithm, and it is only used to generate a diagram with euclidean distance anyway
// TODO Implement fortune's algorithm to generate the diagram when p = 2 (euclidean distance)
void voronoi_diagram(short_map map, vec2 * generators, int generator_quantity, int p){
  for (int i = 0; i < map.height; i ++){
    for (int j = 0; j < map.width; j ++){
      map.map[i][j] = get_closest_gen(generators, generator_quantity, get_vec2(j, i), p);
    }
  }
}

short_map generate_voronoi_diagram(int seed, int size, int divisions, int p){
  short_map map;
  map.height = size;
  map.width = size;
  map.map = (short **)calloc(size, sizeof(short *));
  for (int i = 0; i < size; i ++){
    map.map[i] = (short *)calloc(size, sizeof(short));
  }
  vec2 * center_array = get_center_array(map, divisions);
  int center_quantity = pow(4, divisions);
  move_centers(seed, center_array, center_quantity);
  voronoi_diagram(map, center_array, center_quantity, p);
  free(center_array);

  return map;
}
