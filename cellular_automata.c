#include <stdlib.h>
#include <stdbool.h>
#include "gen_aliases.c"

bool is_within_map_bounds(vec2 point, bool_map map){
    if (point.y < 0 || point.x < 0 || point.y >= map.height || point.x >= map.width){
        return false;
    }
    return true;
}

bool_map generate_cellular_automata(bool_map map, int iterations){
    int f_count;
    bool_map temp_map;
    temp_map.height = map.height;
    temp_map.width = map.width;
    temp_map.map = (bool **)calloc(temp_map.height, sizeof(bool *));
    for (int i = 0; i < temp_map.height; i++){
        temp_map.map[i] = (bool *)calloc(temp_map.width, sizeof(bool));
    }

    for (int i = 0; i < iterations; i ++){
        copy_bool_map(map, temp_map);
        for (int j = 0; j < map.height; j++){
            for (int k = 0; k < map.width; k++){
                f_count = 0;
                for (int y = j - 1; y <= j + 1; y ++){
                    for (int x = k - 1; x <= k + 1; x++){
                        if (is_within_map_bounds(get_vec2(x, y), map)){
                            if (y != j || x != k){
                                if (!temp_map.map[y][x]){
                                    f_count ++;
                                }
                            }
                        }
                        else {
                            f_count ++;
                        }
                    }
                }
                if (f_count > 4){
                    map.map[j][k] = 0;
                } 
                else {
                    map.map[j][k] = 1;
                }
            }
        }
    }

    return map;
}
