#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "entity.h"

#define COW_WIDTH 80
#define COW_HEIGHT 80
#define COW_PRICE 20

Entity init_cow(SDL_Renderer* renderer);