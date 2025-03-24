#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define MAP_WIDTH 15
#define MAP_HEIGHT 15
#define TILE_SIZE 60

extern int tile_map[MAP_HEIGHT][MAP_WIDTH];

void load_tiles(SDL_Renderer *renderer);
void render_map(SDL_Renderer *renderer);