#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;


// This function will set gWindow and gScreenSurface properly
// Notice that we want to change the value of SDL_Window*
// here, so we pass the address of SDL_Window* to the function
void init_background(
    SDL_Window** pgWindow,
    SDL_Surface** pgScreenSurface,
    int SCREEN_WIDTH,
    int SCREEN_HEIGHT
){
    // init window
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        exit(1);
	}
    *pgWindow = SDL_CreateWindow(
        "game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if(*pgWindow == NULL){
        cout << "SDL Window create fail" << endl;
        exit(1);
    }
    // render will be create by SDL_GetWindowSurface
    *pgScreenSurface = SDL_GetWindowSurface(*pgWindow);

    // init music
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		cout << "SDL_Mix could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }
}


SDL_Surface* LoadSurface(string path){
	//Load image from a specified path
	SDL_Surface* surface = IMG_Load(path.c_str());
	if(surface == NULL)	{
		cout << "Unable to load image from" << path.c_str() << endl;
		cout << "SDL_image Error: " << SDL_GetError() << endl;
	}
	return surface;
}


SDL_Texture* LoadTexture(SDL_Renderer* gRenderer, std::string path){
    //Load image from a specified path
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = LoadSurface(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if(newTexture == NULL){
		cout << "Unable to create texture from" << path.c_str() << endl;
		cout << "SDL Error: " << SDL_GetError() << endl;
	}
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}


Mix_Music* LoadMusic(string path){
	//Load music from a specified path
	Mix_Music* music = Mix_LoadMUS(path.c_str());
	if(music == NULL){
		cout << "Unable to load music from" <<  path.c_str() << endl;
	}
	return music;
}
