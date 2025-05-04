#pragma once


#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "entity.h"
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

// extern int money;
// extern int wheat;
// extern int crops;
extern int bucket_limit;
Entity init_player(SDL_Renderer* renderer);