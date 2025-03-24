#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define MAP_WIDTH 15
#define MAP_HEIGHT 15
#define TILE_SIZE 60
#define NUM_MAPS 2
#define collisions(left_x, right_x, top_y, bottom_y) \
    tile_maps[top_y][left_x]==3 || tile_maps[top_y][right_x]==3 || \
    tile_maps[bottom_y][left_x]==3 || tile_maps[bottom_y][right_x]==3 || \
	tile_maps[top_y][left_x]==2 || tile_maps[top_y][right_x]==2 || \
    tile_maps[bottom_y][left_x]==2 || tile_maps[bottom_y][right_x]==2

#define borders(left_x, right_x, top_y, bottom_y) \
	left_x < 0 || right_x >= MAP_WIDTH || top_y < 0 || bottom_y >= MAP_HEIGHT

extern int* maps[NUM_MAPS];
extern int current_map;
extern int (*tile_maps)[MAP_WIDTH];

void load_tiles(SDL_Renderer *renderer);
void render_map(SDL_Renderer *renderer);