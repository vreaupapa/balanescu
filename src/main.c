#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "entity.h"
#include "player.h"

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
    entities[i].render(renderer); \
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

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  QUIT_ENTITIES(entities, entities_count);
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void update() {
  last_tick = current_tick;
  current_tick = SDL_GetTicks();
  delta_time = (current_tick - last_tick) / 1000.0f;
  UPDATE_ENTITIES(entities, entities_count, delta_time);
}

void render() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 155, 0, 255);

  //render for everything
  RENDER_ENTITIES(entities, entities_count, renderer);

  SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  update();
  render();
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  window = SDL_CreateWindow(
    "SDL3 Game",
    800,
    800,
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

  // init_player and put that inside of our entities array
  entities[entities_count++] = init_player(renderer);
  
  return SDL_APP_CONTINUE;
}