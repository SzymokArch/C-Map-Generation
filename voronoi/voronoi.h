#ifndef VORONOI_H
#define VORONOI_H

typedef struct site{
  int y;
  int x;
} site;

site get_center(int, int, int);
site * get_center_array(int, int);
void move_centers(int, site *, int);
short get_closes_site(int, int, site *, int, int);
void voronoi_diagram(short **, int, site *, int, int);
short ** generate_voronoi_diagram(int, int, int, int);

#endif // !VORONOI_H
