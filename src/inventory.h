#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int wheat;
    int crops;
    int milk;
    int coins;
    int bucket;
    int sprint;
} Inventory;

// typedef struct{
//     SDL_Texture* texture;

// }

extern Inventory playerInventory;
extern SDL_Texture* inventoryTexture;

void update_inventory_texture(SDL_Renderer* renderer, TTF_Font* Font);
void render_inventory(SDL_Renderer* renderer);
void init_inventory_textures(SDL_Renderer* renderer);