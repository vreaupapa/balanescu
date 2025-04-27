#include "carti_shop.h"
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

SDL_Texture* carti_shop_texture_handle;
SDL_Texture* texturi_shop[5];
SDL_Texture* crops_price_texture = NULL;
SDL_Texture* milk_price_texture = NULL;
SDL_FRect crops_price_texture_rect = {300, 364, 30, 37};
SDL_FRect milk_price_texture_rect = {400, 364, 30, 37};
TTF_Font* font_crops_price = NULL;


void load_carti_shop(SDL_Renderer *renderer, TTF_Font* font) {
	carti_shop_texture_handle = IMG_LoadTexture(renderer, "./assets/inventory/shop_popup.png");
	if(!carti_shop_texture_handle){
		SDL_Log("eroare incarcare textura cow_shop: %s\n", SDL_GetError());
	}
	texturi_shop[0] = IMG_LoadTexture(renderer, "./assets/Items/crops.png");
	texturi_shop[1] = IMG_LoadTexture(renderer, "./assets/Items/coin.png");
	texturi_shop[2] = IMG_LoadTexture(renderer, "./assets/inventory/buy_button.png");
	texturi_shop[3] = IMG_LoadTexture(renderer, "./assets/Items/milk.png");

	font_crops_price = font;
}

void render_popup_carti(SDL_Renderer *renderer)
{
	SDL_FRect popup_rect = {250, 250, 400, 400};
	SDL_RenderTexture(renderer, carti_shop_texture_handle, NULL, &popup_rect);
	SDL_FRect crops_rect = {300, 300, 60, 60};
	SDL_RenderTexture(renderer, texturi_shop[0], NULL, &crops_rect);
	SDL_FRect buy_rect = {280, 360, 100, 50};
	SDL_RenderTexture(renderer, texturi_shop[2], NULL, &buy_rect);
	SDL_FRect coin_rect = {330, 370, 30, 30};
	SDL_RenderTexture(renderer, texturi_shop[1], NULL, &coin_rect);
    //culoarea textului
    SDL_Color textColor = {255, 255, 255};
	char buycropsText[16];
	snprintf(buycropsText, sizeof(buycropsText), "%d", 5);
    SDL_Surface* cropsSurface = TTF_RenderText_Solid(font_crops_price, buycropsText, strlen(buycropsText), textColor);
    crops_price_texture = SDL_CreateTextureFromSurface(renderer, cropsSurface);
    SDL_DestroySurface(cropsSurface);
	SDL_RenderTexture(renderer, crops_price_texture, NULL, &crops_price_texture_rect);
	SDL_FRect milk_rect = {400, 300, 60, 60};
	SDL_RenderTexture(renderer, texturi_shop[3], NULL, &milk_rect);
	SDL_FRect buy_rect_milk = {380, 360, 100, 50};
	SDL_RenderTexture(renderer, texturi_shop[2], NULL, &buy_rect_milk);
	SDL_FRect coin_rect_milk = {430, 370, 30, 30};
	SDL_RenderTexture(renderer, texturi_shop[1], NULL, &coin_rect_milk);
	char sellmilkText[16];
	snprintf(sellmilkText, sizeof(sellmilkText), "%d", 7);
    SDL_Surface* milkSurface = TTF_RenderText_Solid(font_crops_price, sellmilkText, strlen(sellmilkText), textColor);
    milk_price_texture = SDL_CreateTextureFromSurface(renderer, milkSurface);
	SDL_DestroySurface(milkSurface);
	SDL_RenderTexture(renderer, milk_price_texture, NULL, &milk_price_texture_rect);
}

// static void buy_button(SDL_Renderer *renderer, SDL_Event* event) {
// 	if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT && buton_carti_shop.is_pressed == 1)
// 	{
// 		if(event->button.x > 280 && event->button.x < 380 &&
// 			event->button.y > 360 && event->button.y < 410)
// 			{
// 				SDL_Log("ai apasat butonul de cumparare carti");
// 			}
// 	}
// }

struct Button_popup_carti buton_carti_shop = {4*TILE_SIZE,9*TILE_SIZE,0};