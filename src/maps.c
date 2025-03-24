#include "maps.h"

int tile_map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 2, 2, 0, 0, 0, 1, 1, 1, 1, 0, 0},
    {1, 1, 0, 0, 2, 2, 0, 0, 0, 1, 1, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}
};

SDL_Texture* tile_textures[4];

void load_tiles(SDL_Renderer *renderer) {
    tile_textures[0] = IMG_LoadTexture(renderer, "./assets/Tiles/pixel.jpg");
    tile_textures[1] = IMG_LoadTexture(renderer, "./assets/Tiles/Path_middle.png");
    tile_textures[2] = IMG_LoadTexture(renderer, "./assets/Tiles/Water_Middle.png");
    tile_textures[3] = IMG_LoadTexture(renderer, "./assets/Outdoor decoration/Fences.png");
  
    for (int i = 0; i < 4; i++) {
        if (!tile_textures[i]) {
            SDL_Log("Failed to load tile %d: %s", i, SDL_GetError());
        }
    }
}

static SDL_FRect sprite_frame = {21,0,22,22};
  
void render_map(SDL_Renderer *renderer) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tile_type = tile_map[y][x];
            if(tile_type!=3){
                SDL_FRect dest = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderTexture(renderer, tile_textures[tile_type], NULL, &dest);
            }
        }
    }
    for(int y=2; y < 9; y++){
        SDL_FRect dest = {y*TILE_SIZE, 8*TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_RenderTexture(renderer, tile_textures[3], &sprite_frame, &dest);
    }
}