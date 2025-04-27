#include "cow_shop.h"
#include "maps.h"

// int cow_shop[9][9]={
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// 	{0, 0, 0, 0, 0, 0, 0, 0, 0},
// };

SDL_Texture* cow_shop_texture;

void load_cow_shop(SDL_Renderer *renderer) {
	cow_shop_texture = IMG_LoadTexture(renderer, "./assets/Tiles/pixel_grass.jpg");
	if(!cow_shop_texture){
		SDL_Log("eroare incarcare textura cow_shop: %s\n", SDL_GetError());
	}
}

void render_popup(SDL_Renderer *renderer)
{
	SDL_FRect popup_rect = {100, 100, 700, 700};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
	SDL_RenderFillRect(renderer, &popup_rect); // Fill the rectangle with black color
	for(int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			SDL_FRect tile_rect = {120 + j*TILE_SIZE, 120 + i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
			SDL_RenderTexture(renderer, cow_shop_texture, NULL, &tile_rect);
		}
	}
}

struct Button_popup buton_cow_shop = {4*TILE_SIZE,9*TILE_SIZE,0};