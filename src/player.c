#include "player.h"
#include "maps.h"

static SDL_Texture* player_texture;
static SDL_FRect sprite_frame = {8,5,15,21};

typedef struct{
	float x, y;
} Position;

Position position = {100, 100};

int check_collision(float new_x, float new_y) {
    int left_x   = (int)(new_x / TILE_SIZE);
    int right_x  = (int)((new_x + PLAYER_WIDTH - 3) / TILE_SIZE);
    int top_y    = (int)(new_y / TILE_SIZE);
    int bottom_y = (int)((new_y + PLAYER_HEIGHT - 7) / TILE_SIZE);

    if (borders(left_x, right_x, top_y, bottom_y)) {
        return 3; // coliziune cu marginea hartii
    }

	if (collisions(left_x, right_x, top_y, bottom_y)) {
        return 3; // coliziune
    }
    
    return 0;
}

static void quit(){

}

static void handle_events()
{

}

static void update(float delta_time) {
    float new_x = position.x;
    float new_y = position.y;

    const _Bool *keyboard_state = SDL_GetKeyboardState(NULL);

    if (keyboard_state[SDL_SCANCODE_W]) {
        new_y -= 100 * delta_time;
        if (new_y < 0) {  
            // Dacă trece de marginea sus, schimbă harta și repoziționează
            if (current_map == 0) {  
                current_map = 1;
                tile_maps = (int (*)[MAP_WIDTH])maps[current_map];
                new_y = MAP_HEIGHT * TILE_SIZE - TILE_SIZE;  // Apare jos pe noua hartă
            }
        }
    }

    if (keyboard_state[SDL_SCANCODE_S]) {
        new_y += 100 * delta_time;
		if (new_y > (MAP_HEIGHT * TILE_SIZE - TILE_SIZE) /*&& new_x>(11 * TILE_SIZE) && new_x<(12.20*TILE_SIZE) cod pentru tp specific*/) {
            // Dacă trece de marginea jos, schimbă harta și repoziționează
            if (current_map == 1) {  
                current_map = 0;
                tile_maps = (int (*)[MAP_WIDTH])maps[current_map];
                new_y = 0;  // Apare sus pe noua hartă
            }
        }
    }

    if (keyboard_state[SDL_SCANCODE_A]) {
        new_x -= 100 * delta_time;
        if (new_x < 0) new_x = 0;  // Pentru a bloca la marginea din stanga
    }

    if (keyboard_state[SDL_SCANCODE_D]) {
        new_x += 100 * delta_time;
    }

    if (!check_collision(new_x, position.y)) {
        position.x = new_x;
    }

    if (!check_collision(position.x, new_y)) {
        position.y = new_y;
    }
}

static void render(SDL_Renderer* renderer){
	SDL_FRect player_position = {position.x,position.y,PLAYER_WIDTH,PLAYER_HEIGHT};
	SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);
	SDL_RenderTexture(renderer, player_texture, &sprite_frame, &player_position);
}

Entity init_player(SDL_Renderer* renderer) {

	const char path[] = "./assets/Player/Player.png";
	player_texture = IMG_LoadTexture(renderer, path);

	Entity player = {
		.quit = quit, 
		.handle_events = handle_events, 
		.update = update, 
		.render = render
	};

	return player;
}