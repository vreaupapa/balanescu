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

#define HANDLE_EVENTS_ENTITIES(entities, entities_count, event) \
  for (int i=0; i< entities_count; i++){ \
    entities[i].handle_events(event); \
  }

#define QUIT_ENTITIES(entities, entities_count) \
  for (int i=0; i< entities_count; i++){ \
    entities[i].quit(); \
  }

#define RENDER_ENTITIES(entities, entities_count, renderer) \
  for (int i=0; i< entities_count; i++){ \
    entities[i].render(renderer, &entities[i]); \
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
  //harta pe care umblu
	render_map(renderer);
  //render for button
  render_button(renderer);
  //render for everything
  RENDER_ENTITIES(entities, entities_count, renderer);
  //render pentru inventar
  render_inventory(renderer);
  
  // if (textTexture) {
  //   SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
  // }

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

  init_inventory_textures(renderer);

  //stop test

  //incarc texturi pt fundal
  load_tiles(renderer);

  // init_player and put that inside of our entities array
  entities[entities_count++] = init_cow(renderer, TILE_SIZE * 0.5, TILE_SIZE * 11);
  entities[entities_count++] = init_player(renderer);

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