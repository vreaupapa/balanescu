#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

struct Button_popup_carti
{
	int x, y;
	int is_pressed;
};

void load_carti_shop(SDL_Renderer *renderer, TTF_Font* font);
void render_popup_carti(SDL_Renderer *renderer);
extern struct Button_popup_carti buton_carti_shop;