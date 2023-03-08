// g++ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main_value_noise main_value_noise.cpp && ./main_value_noise

#include "value_noise.c"
#include <stdio.h>
#include <raylib.h>

void draw_greyscale(float_map map){
    for (int i = 0; i < map.height; i ++){
        for (int j = 0; j < map.width; j ++){
            DrawRectangle(j * 2, i * 2, 2, 2, {0, 0, 0, (unsigned char)(255 * map.map[i][j])});
        }
    }
}

void draw_colors(float_map map){
    for (int i = 0; i < map.height; i ++){
        for (int j = 0; j < map.width; j ++){
            if (map.map[i][j] < 0.334){
                Color WATER = {0, (unsigned char)(255 * (map.map[i][j]/0.334)), 255, 255};
                DrawRectangle(j * 2, i * 2, 2, 2, WATER);
            }
            else if (map.map[i][j] < 0.667){
                Color HILL = {0, (unsigned char)(255 - (255 * ((map.map[i][j] - 0.334)/0.334))), 0, 255};
                DrawRectangle(j * 2, i * 2, 2, 2, HILL);
            }
            else{
                Color MOUNTAIN = {(unsigned char)(255 * ((map.map[i][j] - 0.667)/0.334)), (unsigned char)(255 * ((map.map[i][j] - 0.667)/0.334)), (unsigned char)(255 * ((map.map[i][j] - 0.667)/0.334)), 255};
                DrawRectangle(j * 2, i * 2, 2, 2, MOUNTAIN);
            }
        }
    }
}

int main(int argc, char * argv[]){

    int seed;
    int oct;
    double scal;
    printf("Podaj seed, ilosc oktaw, wspolczynnik skalowania: \n");
    scanf("%i %i %lf", &seed, &oct, &scal);

    float_map nmap;
    nmap.height = 513;
    nmap.width = 513;

    srand(seed);

    nmap.map = (float **)calloc(nmap.height, sizeof(float *));
    for (int i = 0; i < nmap.height; i ++){
        nmap.map[i] = (float *)calloc(nmap.width, sizeof(float));
        for (int j = 0; j < nmap.width; j ++){
            nmap.map[i][j] = rand()%1001/1000.;
        }
    }
    
    float_map gmap = multi_octave_value_noise(nmap, oct, scal);
    // float_map gmap = single_octave_value_noise(nmap, oct);

    InitWindow(1280, 720, "main");
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        draw_colors(gmap);
        EndDrawing();
    }
    
    return 0;
}