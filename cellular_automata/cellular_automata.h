#include <stdbool.h>

#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

bool is_within_map_bounds(int y, int x, bool ** map, int size);
void copy_bool_map(bool ** dest, bool ** src, int size);
void cellular_automata(bool ** map, int size, int iterations);
bool ** generate_cellular_automata(int seed, int density, int size, int iterations);

#endif // !CELLULAR_AUTOMATA_H
