#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

#include "../util/util.h"
#include "../object/object.h"
#include "../object/character.h"


// constructe background
const int LEVEL_WIDTH = 3600;
const int LEVEL_HEIGHT = 600;


int** create_bg_array(int LEVEL_WIDTH, int LEVEL_HEIGHT){
    int** background_array = new int* [LEVEL_WIDTH];
    for(int i = 0; i < LEVEL_WIDTH; i++){
        background_array[i] = new int [LEVEL_HEIGHT]();
    }
    return background_array;
}


void destroy_bg_array(int** bg, int LEVEL_WIDTH){
    for(int i = 0; i < LEVEL_WIDTH; i++){
        delete [] bg[i];
    }
    delete [] bg;
}


int game_lv1(
    SDL_Window* gWindow,
    SDL_Surface* gScreenSurface,
    int SCREEN_WIDTH,
    int SCREEN_HEIGHT
){
    // loading page
    SDL_Surface* load_page = NULL;
    load_page = LoadSurface("source/picture/word/load.bmp");
    SDL_BlitScaled(load_page, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);

    // music
    Mix_Music* music = NULL;
    music = LoadMusic("source/music/m2.wav");
    Mix_PlayMusic(music, -1);

    // get render, notice that reader will be create in init_background
    SDL_Renderer* gRenderer = SDL_GetRenderer(gWindow);

    // create background
    int** bg_array = create_bg_array(LEVEL_WIDTH, LEVEL_HEIGHT);
    SDL_Texture* gbackground = NULL;
    gbackground = LoadTexture(gRenderer, "source/picture/background/background1.png");

    // create character
    character person(
        0,
        500-95,
        55,
        95,
        "source/picture/character/go_right.png",
        "source/picture/character/go_left.png",
        gRenderer
    );

    // init flag
    int result = empty;

    // create map
    cout << "____create map___" << endl;
    Map map(bg_array, gRenderer);

    // basic object - static
    map.add_object(0, 500, 550, 100, ground, "source/picture/background/ground1.png");
    map.add_object(800, 500, 300, 100, ground, "source/picture/background/ground2.png");
    map.add_object(2400, 500, 470, 100, ground, "source/picture/background/ground3.png");
    map.add_object(2450, 400, 100, 100, ground, "source/picture/background/ground4.png");
    map.add_object(2670, 430, 200, 70, ground,"source/picture/background/ground5.png");
    map.add_object(2670, 430, 200, 70, ground, "source/picture/background/ground5.png");
    map.add_object(2770, 310, 100, 120, ground, "source/picture/background/ground6.png");
    map.add_object(2670, 240, 200, 70, ground, "source/picture/background/ground7.png");
    map.add_object(2950, 240, 100, 360, ground, "source/picture/background/ground8.png");
    map.add_object(3150, 240, 450, 120, ground, "source/picture/background/ground9.png");
    map.add_object(3150, 480, 450, 120, ground, "source/picture/background/ground10.png");

    map.add_object(200, 380, 100, 18, ground, "source/picture/background/stand.png");
    map.add_object(1500, 120, 400, 200, empty, "source/picture/background/empty.png");
    map.add_object(1500, 400, 350, 18, empty, "source/picture/background/stand.png");

    // basic object - moving
    map.add_object(1077, 380, 150, 15, 1077, 1300, ground, L_and_R, "source/picture/background/stand.png");
    map.add_object(2000, 450, 150, 15, 1900, 2200, ground, L_and_R, "source/picture/background/stand.png");

    // active object

    // this object will become visible after triggered
    map.add_object("invisible_1", 0, 230, 130, 18, 0, 0, invisible, None, "source/picture/background/stand.png");
    map.add_object("invisible_2", 200, 110, 710, 18, 0, 0, invisible, None, "source/picture/background/stand.png");
    
    // this object and some other object will turn to ground when this object is triggered
    map.add_object("event1", 1400, 240, 40, 40, 0, 0, event1, None, "source/picture/background/event1.png");
    map.add_object("event1-a", 1500, 120, 400, 2, 0, 0, empty, None, "source/picture/background/background1.png");
    
    // this object will be invisible and let event2-a start to move
    map.add_object("event2", 2672, 310, 98, 120, 0, 0, event2, None, "source/picture/background/event2.png");
    map.add_object("event2-a", 2570, 240, 100, 18, 135, 285, ground, None, "source/picture/background/stand.png");

    // will be invisible after triggered and let win visible
    map.add_object("event3", 3150, 360, 450, 120, 0, 0, event3, None, "source/picture/background/event3.png");
    map.add_object("event3-a", 3500, 360, 100, 120, 0, 0, invisible, None, "source/picture/background/win.png");

    // monster
    map.add_object("monster1", 450, 450, 50, 50, 0, 0, monster, Monster, "source/picture/background/monster.png");
    
    // a trick at the end
    map.add_object("event4", 3230, 0, 10, 150, 0, 0, event4, None, "source/picture/background/background1.png");
    map.add_object("event4-a", 3150, 0, 30, 240, 0, 0, empty, None, "source/picture/background/background1.png");
    map.add_object("event4-b", 3530, 190, 50, 50, 0, 0, monster, None, "source/picture/background/monster.png");

    // reach to win
    map.add_object("win", 3540, 120, 60, 120, 0, 0, win, None, "source/picture/background/win2.png");

    // reach to dead
    map.add_object("dead", 0, LEVEL_HEIGHT - 10, LEVEL_WIDTH, 10, 0, 0, dead, None, "");

    cout << "_________________" << endl;

    // set camera
    SDL_Rect camera = {50, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // start the game
    SDL_Event e;
    bool quit = false;
    while(!quit){
        // listen
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
				quit = true;
			}
            else{
                person.handle_event(bg_array, e);
            }
        }
        // move all object
        person.move(bg_array, LEVEL_WIDTH, LEVEL_HEIGHT);
        map.move(bg_array, &person);

        // check every special event(active object)
        result = map.check_event(&person);
        if(result != empty)
            break;

        // set camera's x, y to let person be shown in the 
        // center of the camera
        set_camera(&camera, &person, LEVEL_WIDTH, LEVEL_HEIGHT);

        // show img
        SDL_RenderClear(gRenderer);
        SDL_RenderCopyEx(gRenderer, gbackground , &camera, NULL, 0.0, NULL, SDL_FLIP_NONE);
        map.render(&camera);
        person.render(gRenderer, &camera);
        SDL_RenderPresent(gRenderer);
    }

    // free memory
    destroy_bg_array(bg_array, LEVEL_WIDTH);
    map.clean();
    Mix_FreeMusic(music);

    return result;
}

