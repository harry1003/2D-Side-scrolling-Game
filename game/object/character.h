#ifndef _CHARACTER_H_
#define _CHARACTER_H_


#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#include "../util/util.h"


class character{
public:
	character(int, int, int, int, string, string, SDL_Renderer*);
    ~character(){
        SDL_DestroyTexture(go_right);
        SDL_DestroyTexture(go_left);
    }
    // function
    void handle_event(int**, SDL_Event &e);
    void move(int**, int, int);
    void render(SDL_Renderer*, SDL_Rect*);

    bool on_the_ground(int**);
    bool check_top(int**);
    bool check_left(int**);
    bool check_right(int**, int);

    int get_vy(){return v_y;}

    SDL_Texture* get_img();

    // var
    SDL_Rect place;

private:
    bool _right;
    SDL_Texture* go_right;
    SDL_Texture* go_left;
	int v_x, v_y;
};

void set_camera(SDL_Rect*, character*, int, int);
#endif