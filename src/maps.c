
#include "maps.h"

Button button = { BUTTON_X, BUTTON_Y, 60, 60};

int tile_map[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 3, 3, 8, 8, 8, 8, 8, 0, 1, 1, 0},
    {0, 1, 1, 0, 3, 3, 8, 8, 8, 8, 8, 0, 1, 1, 0},
    {0, 1, 1, 0, 3, 3, 8, 8, 8, 8, 8, 0, 1, 1, 0},
    {0, 1, 1, 0, 3, 3, 8, 8, 8, 8, 8, 0, 1, 1, 0},
    {0, 1, 1, 0, 3, 3, 8, 8, 8, 8, 8, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int map2[MAP_HEIGHT][MAP_WIDTH] = { 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}
};


int* maps[NUM_MAPS] = { (int*)tile_map, (int*)map2 };
int current_map = 0;

int (*tile_maps)[MAP_WIDTH] = tile_map;

SDL_Texture* tile_textures[10];
SDL_Texture* carti_shop_texture;
SDL_Texture* tree_texture;

// void activate_button() {
//     if (money >= button.price) {
//         money -= button.price;
//         SDL_Log("Ai cumpărat un obiect! Bani rămași: %d", money);
//     } else {
//         SDL_Log("Nu ai destui bani!");
//     }
// }

void load_tiles(SDL_Renderer *renderer) {
    tile_textures[0] = IMG_LoadTexture(renderer, "./assets/Tiles/pixel.jpg");
    tile_textures[1] = IMG_LoadTexture(renderer, "./assets/Tiles/Path_middle.png");
    tile_textures[2] = IMG_LoadTexture(renderer, "./assets/Tiles/Water_Middle.png");
    tile_textures[3] = IMG_LoadTexture(renderer, "./assets/Tiles/FarmLand_Tile_no_water.png");
    tile_textures[4] = IMG_LoadTexture(renderer, "./assets/Tiles/plantat.png");
    tile_textures[5] = IMG_LoadTexture(renderer, "./assets/Tiles/plantat1.png");
    tile_textures[6] = IMG_LoadTexture(renderer, "./assets/Tiles/plantat2.png");
    tile_textures[7] = IMG_LoadTexture(renderer, "./assets/Tiles/plantat3.png");
    tile_textures[8] = IMG_LoadTexture(renderer, "./assets/Tiles/FarmLand_Tile_locked.png");
    carti_shop_texture = IMG_LoadTexture(renderer, "./assets/carti/carti.png");
    tree_texture = IMG_LoadTexture(renderer, "./assets/Outdoor decoration/Oak_Tree.png");
  
    for (int i = 0; i < 8; i++) {
        if (!tile_textures[i]) {
            SDL_Log("Failed to load tile %d: %s", i, SDL_GetError());
        }
    }
    if(!carti_shop_texture) {
        SDL_Log("Failed to load carti shop texture: %s", SDL_GetError());
    }
    if(!tree_texture) {
        SDL_Log("Failed to load tree texture: %s", SDL_GetError());
    }
}

static SDL_FRect sprite_frame = {21,0,22,22};

void render_button(SDL_Renderer *renderer) {
    if(current_map == 0) {
        SDL_FRect button_rect = { button.x, button.y, button.width, button.height };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Roșu
        SDL_RenderFillRect(renderer, &button_rect);
    }
}
  
void render_map(SDL_Renderer *renderer) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tile_type = tile_maps[y][x];
            SDL_FRect dest = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderTexture(renderer, tile_textures[tile_type], NULL, &dest);
        }
    }
    // for(int y=2; y < 9; y++){
    //     SDL_FRect dest = {y*TILE_SIZE, 8*TILE_SIZE, TILE_SIZE, TILE_SIZE};
    //     SDL_RenderTexture(renderer, tile_textures[3], &sprite_frame, &dest);
    // }
    if(current_map == 1 && tree_texture) {
        SDL_FRect tree_rect = {3 * TILE_SIZE, 1 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect);
        SDL_FRect tree_rect2 = {9 * TILE_SIZE, 1 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect2);
        SDL_FRect tree_rect3 = {3 * TILE_SIZE, 7 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect3);
        SDL_FRect tree_rect4 = {9 * TILE_SIZE, 7 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect4);
        SDL_FRect tree_rect5 = {3 * TILE_SIZE, 11 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect5);
        SDL_FRect tree_rect6 = {9 * TILE_SIZE, 11 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect6);
        SDL_FRect tree_rect7 = {0 * TILE_SIZE, 1 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect7);
        SDL_FRect tree_rect8 = {12 * TILE_SIZE, 1 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect8);
        SDL_FRect tree_rect9 = {5.8 * TILE_SIZE, 0.5 * TILE_SIZE, 200, 240};
        SDL_RenderTexture(renderer, tree_texture, NULL, &tree_rect9);
    }
}

void render_carti(SDL_Renderer *renderer){
    if(current_map == 1){
        
        SDL_FRect carti_rect = { 7*TILE_SIZE, 5*TILE_SIZE, 60,  120};
        SDL_SetTextureScaleMode(carti_shop_texture, SDL_SCALEMODE_NEAREST);
        SDL_RenderTexture(renderer, carti_shop_texture, NULL, &carti_rect);
    }
}
