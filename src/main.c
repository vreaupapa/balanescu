#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* player_texture;

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
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

}

void render() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 155, 0, 255);
  // draw our character
  SDL_FRect sprite_frame = {8,5,15,21};
  SDL_FRect player_position = {250,250,100,100};
  SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);
  SDL_RenderTexture(renderer, player_texture, &sprite_frame, &player_position);

  SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
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

  const char path[] = "./assets/Player/Player.png";
  player_texture = IMG_LoadTexture(renderer, path);
  
  return SDL_APP_CONTINUE;
}