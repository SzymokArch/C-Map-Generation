#include <stdbool.h>

#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

bool is_within_map_bounds(int, int, bool **, int);
void copy_bool_map(bool **, bool **, int);
void cellular_automata(bool **, int, int);
bool ** generate_cellular_automata(int, int, int, int);

#endif // !CELLULAR_AUTOMATA_H
