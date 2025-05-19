#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "entity.h"
//#include "player.h"
#include "maps.h"
#include "cow.h"
#include "inventory.h"
#include "cow_shop.h"
#include "carti_shop.h"
#include "player.h"

#define HANDLE_EVENTS_ENTITIES(entities, entities_count, event) \
  for (int i=0; i< entities_count; i++){ \
    entities[i].handle_events(event, &entities[i]); \
  }

#define QUIT_ENTITIES(entities, entities_count) \
  for (int i=0; i< entities_count; i++){ \
    entities[i].quit(); \
  }

#define RENDER_ENTITIES(entities, entities_count, renderer) \
  for (int i=0; i< entities_count; i++){ \
    entities[i].render(renderer, &entities[i]); \
  }

#define RENDER_SHOP_ENTITIES(entities, entities_count, renderer) \
  for (int i=1; i< entities_count; i++){ \
    if(i<=5) \
    entities[i].render_shop(renderer, &entities[i], 0); \
    else \
    entities[i].render_shop(renderer, &entities[i], 1); \
  }

#define UPDATE_ENTITIES(entities, entities_count, delta_time) \
  for (int i=0; i< entities_count; i++){ \
    entities[i].update(delta_time); \
  }


SDL_Window* window;
SDL_Renderer* renderer;

Entity entities[MAX_ENTITIES];
int entities_count = 0;

Uint64 last_tick = 0;
Uint64 current_tick = 0;
float delta_time;
int play_button=0;
const int FPS = 165;
const int frameDelay = 1000/ FPS; // timpul in milisecunde per cadru

Button farm[36];


TTF_Font* font = NULL;
// SDL_Texture* inventoryTexture = NULL;
// SDL_FRect inventoryFRect;

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  QUIT_ENTITIES(entities, entities_count);
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  //SDL_DestroyTexture(textTexture);
  //TTF_CloseFont(font);
  TTF_Quit();
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {

  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }

  HANDLE_EVENTS_ENTITIES(entities, entities_count, event);

  //verificam daca apas pe escape
  if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE && event->key.repeat == 0 && event->key.down) {
    play_button=0;
  }

  
	if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT && buton_carti_shop.is_pressed == 1)
	{
		if(event->button.x > 280 && event->button.x < 370 &&
			event->button.y > 360 && event->button.y < 410)
			{
        if(playerInventory.coins >= 5)
        {
				playerInventory.crops++;
        playerInventory.coins-=5;
        }
        else
        {
          SDL_Log("Nu ai destui bani!");
        }
			}
    if(event->button.x > 380 && event->button.x < 480 &&
      event->button.y > 360 && event->button.y < 410)
      {
        if(playerInventory.milk > 0)
        {
          playerInventory.milk--;
          playerInventory.coins+=7;
        }
        else
        {
          SDL_Log("Nu ai destul lapte!");
        }
      }

    if(event->button.x > 480 && event->button.x < 580 &&
      event->button.y > 360 && event->button.y < 410)
      {
        if(playerInventory.coins >= 40)
        {
          bucket_limit++;
          playerInventory.coins-=40;
        }
        else
        {
          SDL_Log("Nu ai destui bani!");
        }
      }

    if(event->button.x > 280 && event->button.x < 370 &&
      event->button.y > 510 && event->button.y < 560)
      {
        if(playerInventory.coins >= 100 && playerInventory.sprint == 0)
        {
          playerInventory.coins-=100;
          playerInventory.sprint=1;
        }
        else
        {
          SDL_Log("Nu ai destui bani!");
        }
      }
    }
  //i want to detect the mouse position if i click on the play button
  if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT && play_button == 0)
  {
    if(event->button.x > 300 && event->button.x < 600 &&
      event->button.y > 350 && event->button.y < 450)
    {
      play_button=1;
    }
    //if i press on the exit button it will close the game
    if(event->button.x > 300 && event->button.x < 600 &&
      event->button.y > 500 && event->button.y < 600)
    {
      return SDL_APP_SUCCESS;
    }
  }

  return SDL_APP_CONTINUE;
}

void update() {
  last_tick = current_tick;
  current_tick = SDL_GetTicks();
  delta_time = (current_tick - last_tick) / 1000.0f;
  UPDATE_ENTITIES(entities, entities_count, delta_time);
  update_inventory_texture(renderer, font);
}


void render() {
  SDL_RenderClear(renderer);
  if(play_button==0)
  {
    //i want to just put a photo on the whole screen
    SDL_FRect background_rect = {0, 0, 900, 900};
    SDL_Texture* background_texture = IMG_LoadTexture(renderer, "./assets/Outdoor decoration/background.jpg");
    SDL_RenderTexture(renderer, background_texture, NULL, &background_rect);
    SDL_FRect button_rect = { 300, 350, 300, 100};
    SDL_Texture* button_texture = IMG_LoadTexture(renderer, "./assets/Outdoor decoration/play_button.png");
    SDL_RenderTexture(renderer, button_texture, NULL, &button_rect);
    SDL_FRect title_rect = { 200, 100, 500, 160};
    SDL_Texture* title_texture = IMG_LoadTexture(renderer, "./assets/Outdoor decoration/title.png");
    SDL_RenderTexture(renderer, title_texture, NULL, &title_rect);
    SDL_FRect exit_rect = { 300, 500, 300, 100};
    SDL_Texture* exit_texture = IMG_LoadTexture(renderer, "./assets/Outdoor decoration/exit_button.png");
    SDL_RenderTexture(renderer, exit_texture, NULL, &exit_rect);
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(button_texture);
    SDL_DestroyTexture(title_texture);
  }
  else{
    //harta pe care umblu
    render_map(renderer);
    //render for button
    render_button(renderer);
    //render for everything
    RENDER_ENTITIES(entities, entities_count, renderer);
    
    // if (textTexture) {
    //   SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
    // }

    if(buton_cow_shop.is_pressed)
    {
      render_popup(renderer);
      RENDER_SHOP_ENTITIES(entities, entities_count, renderer);
    }
    //render carti shop
    render_carti(renderer);
    if(buton_carti_shop.is_pressed)
    {
      render_popup_carti(renderer);
    }
    //render pentru inventar
    render_inventory(renderer);
  }
  SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  Uint32 frameStart = SDL_GetTicks(); //timpul de start al frame-ului
  update();
  render();

  int frameTime = SDL_GetTicks()-frameStart; //Timpul cat a durat frame-ul

  //daca frame ul a durat mai putin decat timpul dorit, asteptam restul
  if(frameTime < frameDelay)
  {
    SDL_Delay(frameDelay-frameTime);
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Inițializează SDL_ttf
  if (TTF_Init() == -1) {
    SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
    return -1;
  }

  window = SDL_CreateWindow(
    "Farming Simulator",
    900,
    900,
    0
  );

  if (!window) {
    SDL_Log("Error creating window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, NULL);

  if (!renderer) {
    SDL_Log("Error creating renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  //test
  
    //Încarcă fontul
    font = TTF_OpenFont("./Fonts/joystix monospace.ttf", 32);
    if (!font) {
        SDL_Log("Eroare încărcare font: %s\n", SDL_GetError());
        return -1;
    }
    //test
    // SDL_Color textColor = {255, 255, 255};
    // SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL_ttf!", 15, textColor);
    // if(!textSurface)
    // {
    //   SDL_Log("Eroare creare suprafata text:%s \n", SDL_GetError());
    //   return -1;
    // }
    // textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    // if (!textTexture) {
    //   SDL_Log("Eroare creare textură text: %s\n", SDL_GetError());
    //   return -1;
    // }

    //update_inventory_texture(renderer, font);

    
  // textRect.x = 100;
  // textRect.y = 100;
  // textRect.w = textSurface->w;
  // textRect.h = textSurface->h;

  //SDL_DestroySurface(textSurface);

  //test 2 pentru inventar

  playerInventory.coins = 100;

  init_inventory_textures(renderer);

  //stop test

  //incarc texturi pt fundal
  load_tiles(renderer);
  //incarc texturi pt zona de cow shop
  load_cow_shop(renderer);
  //incarc texturi pt zona de carti shop
  load_carti_shop(renderer, font);

  // init_player and put that inside of our entities array
  entities[entities_count++] = init_player(renderer);
  entities[entities_count++] = init_cow(renderer, TILE_SIZE * 0.5, TILE_SIZE * 11);

  //incarc locatiile de la butoane
  int y=-1;
  for(int i=1; i<36; i++)
  {
    farm[i].x=TILE_SIZE*(5+((i-2)%7));
    if((i-1)%7==0)
      y++;
    farm[i].y=TILE_SIZE*(1+y);
    farm[i].height=TILE_SIZE;
    farm[i].width=TILE_SIZE;
  }
  
  return SDL_APP_CONTINUE;
}