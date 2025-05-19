#include "player.h"
#include "maps.h"
#include "cow.h"
#include "entity.h"
#include "inventory.h"
#include "cow_shop.h"
#include "carti_shop.h"

SDL_Renderer* renderer_cow;
static SDL_Texture* player_texture;
static SDL_FRect sprite_frame = {8,5,15,21};
//int money = 100; // bani initiali
int farm_time[5][7] = {0}; // timpul de crestere al plantelor
int bucket_limit = 1;

typedef struct{
	float x, y;
} Position_player;

Position_player position_player = {100, 100};

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

int is_near_button_cow() {
    return (position_player.x>BUTTON_X && position_player.x<BUTTON_X+TILE_SIZE \
        && position_player.y >BUTTON_Y && position_player.y < BUTTON_Y+TILE_SIZE);
}
int is_near_button_farm() {
    return(position_player.x>farm[1].x && position_player.x<farm[7].x+TILE_SIZE \
        && position_player.y >farm[1].y && position_player.y < farm[35].y+TILE_SIZE);
}

int is_near_button_cow_shop() {
    return(position_player.x>buton_cow_shop.x && position_player.x<buton_cow_shop.x+TILE_SIZE \
        && position_player.y >buton_cow_shop.y && position_player.y < buton_cow_shop.y+TILE_SIZE);
}

int is_near_button_carti_shop() {
    return(position_player.x>buton_carti_shop.x && position_player.x<buton_carti_shop.x+(3*TILE_SIZE) \
        && position_player.y >buton_carti_shop.y && position_player.y < buton_carti_shop.y+(4*TILE_SIZE));
}

int is_near_water() {
    return((tile_maps[(int)(position_player.y/TILE_SIZE)][(int)(position_player.x/TILE_SIZE)+1]==2) || 
        (tile_maps[(int)(position_player.y/TILE_SIZE)][(int)(position_player.x/TILE_SIZE)-1]==2) || 
        (tile_maps[(int)(position_player.y/TILE_SIZE)+1][(int)(position_player.x/TILE_SIZE)]==2) || 
        (tile_maps[(int)(position_player.y/TILE_SIZE)-1][(int)(position_player.x/TILE_SIZE)]==2));
}

static void quit(){

}

int y_cow=0;
int x_cow=1; // tile-urile in functie de vacile cumparate

static void handle_events(SDL_Event *event, Entity* this)
{
    
    if(event->key.key == SDLK_E && event->key.repeat == 0 \
        && event->key.down && is_near_button_cow() && current_map == 0){
        if(playerInventory.coins>=COW_PRICE && x_cow<10)
        {
            playerInventory.coins-=COW_PRICE;
            SDL_Log("Ai cumparat o vaca!\nMai ai %d bani!", playerInventory.coins);
            entities[entities_count++] = init_cow(renderer_cow, TILE_SIZE*(0.5+(((x_cow)%5)*2)), TILE_SIZE*(11+y_cow*1.5));
            x_cow++;
            if(x_cow %5 == 0)
            {
                //SDL_Log("Ai 5 vaci!\nAi primit 100 de bani!");
                //playerInventory.coins+=100;
                y_cow++;
            }
        }
        else{
            if(x_cow<10)
                SDL_Log("Nu ai destui bani! ");
            else
                SDL_Log("Ai cumparat maximul de vaci!");
        }

    }
    //daca apas pe buton fac astfel incat sa nu fie apasat de mai multe ori
    if(event->key.key == SDLK_E && event->key.repeat == 0 \
        && event->key.down && is_near_button_farm() && current_map == 0){
        

        if(tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]==4 && playerInventory.bucket>0){
            tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]=5;
            farm_time[(int)position_player.y/TILE_SIZE-1][(int)position_player.x/TILE_SIZE-4]=SDL_GetTicks();
            playerInventory.bucket--;
        }
        //daca e neplantata bucata de pamant si inca am crops valabile, pot planta
        if(tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]==3 && playerInventory.crops>0){
            tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]=4;
            // timpul de plantare incepe
            //farm_time[(int)position_player.y/TILE_SIZE-1][(int)position_player.x/TILE_SIZE-4]=SDL_GetTicks();
            playerInventory.crops--;
        }
        if(tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]==8 && playerInventory.coins>=25){
            tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]=3;
            playerInventory.coins-=25;
        }
        //daca a crescut, pot recolta
        if(tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]==7){
            tile_maps[(int)position_player.y/TILE_SIZE][(int)position_player.x/TILE_SIZE]=3;//recoltam
            playerInventory.wheat++;
            SDL_Log("acum ai %d grau!", playerInventory.wheat);
        }
    }
    if(event->key.key == SDLK_E && event->key.repeat == 0 \
        && event->key.down && is_near_button_cow_shop() && current_map == 0){
            if(buton_cow_shop.is_pressed == 0)
            {
                SDL_Log("ai apasat butonul cow shop");
                buton_cow_shop.is_pressed = 1;
            }
            else
            {
                SDL_Log("ai apasat din nou butonul cow shop");
                buton_cow_shop.is_pressed = 0;
            }
        }
    if(event->key.key == SDLK_E && event->key.repeat == 0 \
        && event->key.down && is_near_button_carti_shop() && current_map == 1){
            if(buton_carti_shop.is_pressed == 0)
            {
                SDL_Log("ai apasat butonul cow shop");
                buton_carti_shop.is_pressed = 1;
            }
            else
            {
                SDL_Log("ai apasat din nou butonul cow shop");
                buton_carti_shop.is_pressed = 0;
            }
        }

    
    if(event->key.key == SDLK_E && event->key.repeat == 0 \
        && event->key.down){
            SDL_Log("%d %d", (int)position_player.x/TILE_SIZE, (int)position_player.y/TILE_SIZE);
        }

    if(event->key.key == SDLK_E && event->key.repeat == 0 \
        && event->key.down && is_near_water()){
            if(playerInventory.bucket < bucket_limit)
                playerInventory.bucket++;
        }
}

//280, 360, 100, 50

static void update(float delta_time) {
    if(!buton_cow_shop.is_pressed && !buton_carti_shop.is_pressed){//oprim movementul cand e deschis cow sau carti shop
        float new_x = position_player.x;
        float new_y = position_player.y;
        //variabila pentru bani primiti pasiv
        //static int last_time_for_money = 0;

        const _Bool *keyboard_state = SDL_GetKeyboardState(NULL);

        //verificam daca trec 5 secunde de la plantare
        for(int i=0; i<5; i++){
            for(int j=0; j<7; j++){
                if(farm_time[i][j] != 0 && SDL_GetTicks()-farm_time[i][j] > 5000)
                {
                    if(tile_map[i+1][j+4]==6)
                    {
                        tile_map[i+1][j+4]=7;
                        farm_time[i][j]=0;
                    }
                    if(tile_map[i+1][j+4]==5)
                    {
                        tile_map[i+1][j+4]=6;
                        farm_time[i][j]=SDL_GetTicks();
                    }
                    
                }
            }
        }

        if (keyboard_state[SDL_SCANCODE_W]) {
            new_y -= 100 * delta_time;
            if(keyboard_state[SDL_SCANCODE_LSHIFT] && playerInventory.sprint == 1)
                new_y -= 100*delta_time;
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
            if(keyboard_state[SDL_SCANCODE_LSHIFT] && playerInventory.sprint == 1)
                new_y += 100*delta_time;
            if (new_y > (MAP_HEIGHT * TILE_SIZE - TILE_SIZE) \
            /*&& new_x>(11 * TILE_SIZE) && new_x<(12.20*TILE_SIZE) cod pentru tp specific*/) {
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
            if(keyboard_state[SDL_SCANCODE_LSHIFT] && playerInventory.sprint == 1)
                new_x -= 100*delta_time;
            if (new_x < 0) new_x = 0;  // Pentru a bloca la marginea din stanga
        }

        if (keyboard_state[SDL_SCANCODE_D]) {
            new_x += 100 * delta_time;
            
            if(keyboard_state[SDL_SCANCODE_LSHIFT] && playerInventory.sprint == 1)
                new_x += 100*delta_time;
        }

        if (!check_collision(new_x, position_player.y)) {
            position_player.x = new_x;
        }

        if (!check_collision(position_player.x, new_y)) {
            position_player.y = new_y;
        }
    }
    // sistem pasiv de bani
    
    // uint32_t current_time = SDL_GetTicks();
    // if(current_time-last_time_for_money > 5000)
    // {
    //     money+=20;
    //     SDL_Log("Ai primit 20 de bani!");
    //     last_time_for_money = current_time;
    // } // primesti 20 de bani pasiv o data la 5 secunde
}

static void render(SDL_Renderer* renderer, Entity* this){
	SDL_FRect player_position = {position_player.x,position_player.y,PLAYER_WIDTH,PLAYER_HEIGHT};
	SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);
	SDL_RenderTexture(renderer, player_texture, &sprite_frame, &player_position);
}

Entity init_player(SDL_Renderer* renderer) {
    renderer_cow = renderer;
	const char path[] = "./assets/Player/Player.png";
	player_texture = IMG_LoadTexture(renderer, path);

	Entity player = {
		.quit = quit,
		.handle_events = handle_events,
		.update = update,
		.render = render,
	};

	return player;
}