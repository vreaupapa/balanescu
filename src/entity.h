#pragma once
#include <SDL3/SDL.h>
#define MAX_ENTITIES 100

typedef struct {
    float x, y;
} Position;

typedef struct Entity Entity;

struct Entity {
	void(*quit)(void);
	void(*handle_events)(SDL_Event*);
	void(*update)(float);
	void (*render)(SDL_Renderer*, struct Entity*);
	Position position;
};

extern int entities_count;
extern Entity entities[MAX_ENTITIES];