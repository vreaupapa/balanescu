#include "cow.h"
#include "entity.h"
#include "maps.h"

static SDL_Texture* cow_texture;
static SDL_FRect sprite_frame = {5,6,24,21};
static SDL_FRect sprite_frame_2={37,7,24,20};

int anim=0;

static void quit(){

}

static void handle_events()
{

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

Entity init_cow(SDL_Renderer* renderer, float x, float y) {
	const char path[] = "./assets/Animals/Cow/Cow.png";
	
	cow_texture = IMG_LoadTexture(renderer, path);
	if (!cow_texture) {
		SDL_Log("Eroare la încărcarea texturii vacii: %s", SDL_GetError());
		return (Entity){0};
	}

	Entity cow = {
		.quit = quit, 
		.handle_events = handle_events, 
		.update = update,
		.render = render,
		.position = {x, y}
	};

	return cow;
}