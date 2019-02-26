#include<SDL2/SDL.h>
#include <iostream>
using namespace std;

#include "./menu/menu.h"
#include "./map/level1.h"
#include "./util/util.h"


// window
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

int main(){
    // create window, surface, render
    init_background(
        &gWindow,
        &gScreenSurface,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    start_page(gWindow, gScreenSurface);

    /* 
    Todo: 
    1. write a menu such that we can change from different level
    2. save function 
    */

    bool quit = false;
    while(!quit){
        int end = game_lv1(
            gWindow,
            gScreenSurface,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        );
        quit = end_page(gWindow, gScreenSurface, end);
    }

}
