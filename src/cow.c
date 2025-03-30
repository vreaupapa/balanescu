#include "cow.h"
#include "entity.h"
#include "maps.h"

static SDL_Texture* cow_texture;
static SDL_FRect sprite_frame = {5,6,24,21};

static void quit(){

}

static void handle_events()
{

}

static void update(float delta_time) {

}

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

	Entity cow = {
		.quit = quit, 
		.handle_events = handle_events, 
		.update = update,
		.render = render,
		.position = {x, y}
	};

	return cow;
}