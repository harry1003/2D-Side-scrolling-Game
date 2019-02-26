#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#include "../util/util.h"
#include "character.h"


// you should change object.cpp too if you want to change this
int delay = 6;
int jump_high = 150;
int up_v = 5;
int character_VEL = 3;


character::character(
	int PosX,
	int PosY,
	int WIDTH,
	int HEIGHT,
	string right,
	string left,
	SDL_Renderer* gRenderer
){
	place.x = PosX;
	place.y = PosY;
	place.w = WIDTH;
	place.h = HEIGHT;
	v_x = 0;
	v_y = 0;
	go_right = LoadTexture(gRenderer, right);
	go_left = LoadTexture(gRenderer, left);
	_right = true;
}


void character::render(SDL_Renderer* gRenderer, SDL_Rect* camera){
	SDL_Rect show_character = this->place;
    show_character.x = this->place.x - camera->x;
    show_character.y = this->place.y - camera->y;
	SDL_RenderCopyEx(gRenderer, this->get_img(), NULL, &show_character, 0.0, NULL, SDL_FLIP_NONE);
}


void character::handle_event(int** bg, SDL_Event &e){
	// jump
	if(on_the_ground(bg) && e.key.keysym.sym == SDLK_UP){
		v_y = -up_v * 2;
	}

	// key was pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //start to move
        switch(e.key.keysym.sym)
        {
            case SDLK_LEFT: 
			    v_x -= character_VEL;
			    _right = false;
			    break;
            case SDLK_RIGHT: 
			    v_x += character_VEL; 
			    _right = true;
			    break;
        }
    }
    //key was released
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        // stop moving
        if(v_x != 0){
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT: v_x += character_VEL; break;
                case SDLK_RIGHT: v_x -= character_VEL; break;
            }
        }
    }
}


void character::move(int** bg, int WIDTH, int HEIGHT){
    // moving down
    int move_y = 0;
    if(!on_the_ground(bg)){
        // gravity, if not on the ground, 
        // you pretend to fall
        move_y = move_y + up_v;
    }
    // moving up
    static int times = 0;
    if(v_y < 0)
        // v_y < 0 for jumping
        times++;
    if(times >= (jump_high / up_v) || !check_top(bg)){
        // when reached jump_high or collision at top
        // stop jumping
        // !check_top for top is not empty
        v_y = 0;
        times = 0;
    }
    move_y = move_y + v_y;

    while(move_y != 0){
        if(move_y < 0){
            // moving up
            if(check_top(bg)){
                place.y = place.y - 1;
                move_y = move_y + 1;
            }
            else
                break;
        }
        else if(move_y > 0){
            // moving down
            if(!on_the_ground(bg) && place.y < HEIGHT){
                place.y = place.y + 1;
                move_y = move_y - 1;
            }
            else
                break;  
        }
    }
    
    // right and left
    int move_x = v_x;
    while(move_x != 0){
        if(move_x > 0){
            // character go right
            if(check_right(bg, WIDTH)){
                place.x = place.x + 1;
                move_x = move_x - 1;
            }
            else
                break;
        }
        else if(move_x < 0){
            // character go left
            if(check_left(bg)){
                place.x = place.x - 1;
                move_x = move_x + 1;
            }
            else
                break;
        }
    }
    SDL_Delay(delay);
}


// this function will check if the character
// is standing on the ground
bool character::on_the_ground(int** bg){
    for(int i = place.x; i < place.w + place.x; i++){
        // notice that the object is actually
        // place.x ~ place.x + place.w - 1
        // place.y ~ place.y + place.h - 1
        // in bg, so place.y + place.h
        // is the next pixel under the object
        if(bg[i][place.y + place.h] == ground){
            return true;
        }
    }
    return false;
}


// the three function below will check if the 
// the character will go out of the boundary
// or is empty. Notice that if it is not empty,
// the character will not move.
bool character::check_left(int** bg){
    // when going left, you need to make sure that
    // the character will not go out of the bg
    int bound = place.x - 1;
    if(bound < 0)
        return false;
    // check if empty
    for(int i = place.y; i < place.y + place.h; i++){
        if(bg[bound][i] != empty){
            return false;
        }
    }
    return true;
}


bool character::check_right(int** bg, int WIDTH){
    // when going right, you need to make sure that
    // the character will not go out of the bg
    int bound = place.x + place.w;
    if(bound >= WIDTH)
        return false;
    // check if empty
    for(int i = place.y; i < place.y + place.h; i++){
        if(bg[bound][i] != empty)
            return  false;
    }
    return true;
}


bool character::check_top(int** bg){
    // check if out of bound
    int bound = place.y - 1;
    if(bound < 0)
        return false;
    // check empty
    for(int i = place.x; i < place.x + place.w; i++){
        if(bg[i][bound] != empty)
            return false;
    }
    return true;
}


// return right img to show
SDL_Texture* character::get_img(){
	if(_right)
        return go_right;
    else
        return go_left;
}


// this function will properly set camera's place 
// such that we can show our person in the center
void set_camera(SDL_Rect* camera, character* person, int LEVEL_WIDTH, int LEVEL_HEIGHT){
    camera->x = (person->place.x + person->place.w / 2) - camera->w / 2;
    camera->y = (person->place.y + person->place.h / 2) - camera->h / 2;
    if(camera->x < 0){ 
		camera->x = 0;
	}
	if(camera->y < 0){
		camera->y = 0;
	}
	if(camera->x + camera->w > LEVEL_WIDTH){
		camera->x = LEVEL_WIDTH - camera->w;
	}
	if(camera->y + camera->h > LEVEL_HEIGHT){
		camera->y = LEVEL_HEIGHT - camera->h;
	}
}