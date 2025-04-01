#include <stdlib.h>
#include <string.h>

#include "gradient_noise.h"

#ifdef RAYLIB_FOUND
#include <raylib.h>
#else
#include "raylib/src/raylib.h"
#endif

char get_ASCII(float a)
{
	char *buff = "$@B%%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/"
		     "\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
	int size = strlen(buff);
	float b = (a + 1) / 2;
	int index = b * (size - 1);
	return buff[index];
}

void draw_greyscale(float **map, int size, short tile_size)
{
	Color clr = {0, 0, 0, 255};
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			clr.a = (unsigned char)(255 * map[i][j]);
			DrawRectangle(j * tile_size, i * tile_size, tile_size,
				      tile_size, clr);
		}
	}
}

Color get_color_from_height(float height)
{
	Color clr = {.a = 255};
	if (height < 0.334) {
		// water
		clr.r = 0;
		clr.g = (uint8_t)(255 * (height / 0.334));
		clr.b = 255;
	}
	else if (height < 0.667) {
		clr.r = 0;
		clr.g = (uint8_t)(255 - (255 * ((height - 0.334) / 0.334)));
		clr.b = 0;
	}
	else {
		clr.r = (uint8_t)(255 * ((height - 0.667) / 0.334));
		clr.g = (uint8_t)(255 * ((height - 0.667) / 0.334));
		clr.b = (uint8_t)(255 * ((height - 0.667) / 0.334));
	}
	return clr;
}

void draw_colors(float **map, int size, short tile_size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			float a = (map[i][j] + 1.0f) / 2.0f;
			DrawRectangle(j * tile_size, i * tile_size, tile_size,
				      tile_size, get_color_from_height(a));
		}
	}
}

int main(void)
{
	float **map = calloc(257, sizeof(float *));
	for (int i = 0; i < 257; i++) {
		map[i] = calloc(257, sizeof(float));
		for (int j = 0; j < 257; j++) {
			map[i][j] =
			    octave_gradient_noise(i / 64., j / 64., 6, 0.5, 25);
		}
	}

	InitWindow(1024, 1024, "Gradient Noise Test");
	while (!(WindowShouldClose())) {
		BeginDrawing();
		{
			ClearBackground(WHITE);
			draw_colors(map, 257, 4);
		}
		EndDrawing();
	}

	for (int i = 0; i < 257; i++) {
		free(map[i]);
	}
	free(map);
}
