#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

#include "./menu.h"
#include "../util/util.h"


void start_page(SDL_Window* gWindow, SDL_Surface* gScreenSurface){
    SDL_Surface* start_page = NULL;
    start_page = LoadSurface("source/picture/word/start.bmp");
    // show picture
    SDL_BlitScaled(start_page, NULL, gScreenSurface, NULL);	
	SDL_UpdateWindowSurface(gWindow);
    // play music
    Mix_Music* music = NULL;
    music = LoadMusic("source/music/m1.wav");
    Mix_PlayMusic(music, -1);
    // check touch
    SDL_Event e;
	do{	
	    SDL_PollEvent(&e);
	}
	while(
        e.type != SDL_KEYDOWN &&
        e.type != SDL_MOUSEBUTTONDOWN
    );
    // go to menu page
    Mix_FreeMusic(music);
    SDL_FreeSurface(start_page);
}


bool end_page(SDL_Window* gWindow, SDL_Surface* gScreenSurface, int end){

    SDL_Surface* page = NULL;

    if(end == win){
        cout << "win" << endl;
        page = LoadSurface("source/picture/word/win.bmp");
    }
    else{
        cout << "dead" << endl;
        page = LoadSurface("source/picture/word/loss.bmp");
    }

    SDL_BlitScaled(page, NULL, gScreenSurface, NULL);	
	SDL_UpdateWindowSurface(gWindow);

    SDL_Delay(1500);

    SDL_Event e;
    SDL_PollEvent(&e);
	do{	
	    SDL_PollEvent(&e);
        if (e.type == SDL_QUIT)
            return true;
	}
	while(
        e.key.keysym.scancode != SDL_SCANCODE_Q &&
        e.key.keysym.scancode != SDL_SCANCODE_R
    );

    if(e.key.keysym.scancode == SDL_SCANCODE_Q){
        return true;
    }
    return false;
}