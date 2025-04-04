#include "inventory.h"

SDL_Texture* inventoryTexture = NULL;
Inventory playerInventory= {0,5};
SDL_FRect inventoryRect;

void update_inventory_texture(SDL_Renderer* renderer, TTF_Font* font){
    if(inventoryTexture)
    {
        SDL_DestroyTexture(inventoryTexture);
    }
}