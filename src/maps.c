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
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}
};

SDL_Texture* tile_textures[3];

void load_tiles(SDL_Renderer *renderer) {
    tile_textures[0] = IMG_LoadTexture(renderer, "./assets/Tiles/pixel.jpg");
    SDL_SetTextureScaleMode(tile_textures[0], SDL_SCALEMODE_NEAREST);
    tile_textures[1] = IMG_LoadTexture(renderer, "./assets/Tiles/Path_middle.png");
    SDL_SetTextureScaleMode(tile_textures[1], SDL_SCALEMODE_NEAREST);
    tile_textures[2] = IMG_LoadTexture(renderer, "./assets/Tiles/Water_Middle.png");
    SDL_SetTextureScaleMode(tile_textures[2], SDL_SCALEMODE_NEAREST);
  
    for (int i = 0; i < 3; i++) {
        if (!tile_textures[i]) {
            SDL_Log("Failed to load tile %d: %s", i, SDL_GetError());
        }
    }
}
  
void render_map(SDL_Renderer *renderer) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tile_type = tile_map[y][x];  
            SDL_FRect dest = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderTexture(renderer, tile_textures[tile_type], NULL, &dest);
        }
    }
}