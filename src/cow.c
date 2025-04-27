#include "cow.h"
#include "entity.h"
#include "maps.h"
#include "cow_shop.h"
#include "inventory.h"

#define button_size 30

static SDL_Texture* cow_texture;
static SDL_Texture* cow_shop_texture;
static SDL_FRect sprite_frame = {5,6,24,21};
static SDL_FRect sprite_frame_2={37,7,24,20};

int anim=0;

static void quit(){

}

static void handle_events(SDL_Event *event, Entity* this)
{
	if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT)
	{
		if((this->position.y-300)<400){
			if(event->button.x > this->position.x+130 && event->button.x < this->position.x + 130+button_size &&
				event->button.y > this->position.y-350 && event->button.y < this->position.y -350 + button_size)
			{
				if(buton_cow_shop.is_pressed && playerInventory.wheat > 0)
				{
					playerInventory.wheat--;
					playerInventory.milk++;
				}
			}
		}
		else{
			if(event->button.x > this->position.x+130 && event->button.x < this->position.x + 130+button_size &&
				event->button.y > this->position.y-210 && event->button.y < this->position.y -210 + button_size)
			{
				if(buton_cow_shop.is_pressed && playerInventory.wheat > 0)
				{
					playerInventory.wheat--;
					playerInventory.milk++;
				}
			}
		}
	}
}

static void update(float delta_time) {
    static uint32_t last_time = 0;
    uint32_t current_time = SDL_GetTicks();

    // Schimbă cadrul de animație la fiecare 500 ms
    if (current_time - last_time > 500) {
        anim = !anim; // Alternează între 0 și 1
        last_time = current_time;
    }

    // Actualizează cadrul sprite-ului în funcție de animație
    if (anim) {
        sprite_frame = sprite_frame_2;
    } else {
        sprite_frame = (SDL_FRect){5, 6, 24, 21};
    }

}
//SDL_Texture *textura = cow_texture;

static void render(SDL_Renderer* renderer, Entity* this){
	if(current_map == 0){
		SDL_FRect cow_position = {this->position.x,this->position.y,COW_WIDTH,COW_HEIGHT};
		SDL_SetTextureScaleMode(cow_texture, SDL_SCALEMODE_NEAREST);
		SDL_RenderTexture(renderer, cow_texture, &sprite_frame, &cow_position);
	}
}

static void render_shop(SDL_Renderer* renderer, Entity* this, int contor){

	if(current_map == 0){
		SDL_FRect cow_position = {this->position.x+130,this->position.y-300,COW_WIDTH,COW_HEIGHT};
		SDL_SetTextureScaleMode(cow_texture, SDL_SCALEMODE_NEAREST);
		SDL_RenderTexture(renderer, cow_texture, &sprite_frame, &cow_position);
		if(contor == 0)//butoane pentru a hrani vacile
		{
			SDL_FRect cow_shop_FRect = {this->position.x+130,this->position.y-350,button_size,button_size};
			SDL_SetTextureScaleMode(cow_shop_texture, SDL_SCALEMODE_NEAREST);
			SDL_RenderTexture(renderer, cow_shop_texture, NULL, &cow_shop_FRect);
		}
		else
		{
			SDL_FRect cow_shop_FRect = {this->position.x+130,this->position.y-210,button_size,button_size};
			SDL_SetTextureScaleMode(cow_shop_texture, SDL_SCALEMODE_NEAREST);
			SDL_RenderTexture(renderer, cow_shop_texture, NULL, &cow_shop_FRect);
		}
	}
}

Entity init_cow(SDL_Renderer* renderer, float x, float y) {
	const char path[] = "./assets/Animals/Cow/Cow.png";
	const char buton_cow_shop[] = "./assets/Tiles/FarmLand_Tile.png";
	
	cow_texture = IMG_LoadTexture(renderer, path);
	if (!cow_texture) {
		SDL_Log("Eroare la încărcarea texturii vacii: %s", SDL_GetError());
		return (Entity){0};
	}

	cow_shop_texture = IMG_LoadTexture(renderer, buton_cow_shop);
	if (!cow_shop_texture) {
		SDL_Log("Eroare la încărcarea texturii buton_cow_shop: %s", SDL_GetError());
		return (Entity){0};
	}

	Entity cow = {
		.quit = quit,
		.handle_events = handle_events,
		.update = update,
		.render = render,
		.render_shop = render_shop,
		.position = {x, y}
	};

	return cow;
}