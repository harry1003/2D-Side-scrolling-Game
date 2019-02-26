#ifndef _UTIL_H_
#define _UTIL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

enum
{
	empty,
	ground,
	monster,
	invisible,
	event1,
	event2,
	event3,
	event4,
	win,
	dead
};

void init_background(SDL_Window**, SDL_Surface**, int, int);

SDL_Surface* LoadSurface(std::string);
SDL_Texture* LoadTexture(SDL_Renderer*, std::string);
Mix_Music* LoadMusic(std::string);
#endif
