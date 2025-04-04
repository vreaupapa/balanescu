#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct {
    int wheat;
    int crops; 
} Inventory;

extern Inventory playerInventory;
void update_inventory_texture(SDL_Renderer* renderer, TTF_Font* Font);