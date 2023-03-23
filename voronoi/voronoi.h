#ifndef VORONOI_H
#define VORONOI_H

typedef struct site{
  int y;
  int x;
} site;

float minkowski_distance(int ay, int ax, int by, int bx, int p);
site get_center(int start_y, int start_x, int pitch);
site * get_center_array(int size, int divisons);
void move_centers(int seed, site * center_array, int center_quantity);
short get_closes_site(int y, int x, site * sites, int site_quantity, int p);
void voronoi_diagram(short ** map, int size, site * sites, int site_quantity, int p);
short ** generate_voronoi_diagram(int seed, int size, int divisions, int p);

#endif // !VORONOI_H
