#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

struct Button_popup
{
	int x, y;
	int is_pressed;
};

void render_popup(SDL_Renderer *renderer);
void load_cow_shop(SDL_Renderer *renderer);

extern struct Button_popup buton_cow_shop;