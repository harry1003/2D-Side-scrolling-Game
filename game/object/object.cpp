#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#include "../util/util.h"
#include "./object.h"


// you should change character.cpp too if you want to change this
int obj_up_v = 5;


// basic object - static
object::object(
    int** bg,
    int PosX,
    int PosY,
    int WIDTH,
    int HEIGHT,
    int e,
    string img_path,
    SDL_Renderer* gRenderer
){
    cout << "create object: " << img_path << endl;
    place.x = PosX;
    place.y = PosY;
    place.w = WIDTH;
    place.h = HEIGHT;
    if(img_path != "")
        picture = LoadTexture(gRenderer, img_path);
    else
        picture = NULL;
    _start = _end = _v = 0;
    _direction = None;
    _event = e;
    // init on the background array
    // only change bg when the property is ground
    if(e == ground){
        for(int i = place.x; i < place.x + place.w; i++){
            for(int j = place.y; j < place.y + place.h; j++){
                bg[i][j] = e;
            }
        }   
    }
}


// basic object - moving
object::object(
    int** bg,
    int PosX,
    int PosY,
    int WIDTH,
    int HEIGHT,
    int start,
    int end,
    int e,
    int direction,
    string img_path,
    SDL_Renderer* gRenderer
){
    cout << "create object " << img_path << endl;
    place.x = PosX;
    place.y = PosY;
    place.w = WIDTH;
    place.h = HEIGHT;
    if(img_path != "")
        picture = LoadTexture(gRenderer, img_path);
    else
        picture = NULL;
    _v = 1;
    _direction = direction;
    _event = e;
    _start = start;
    _end = end;

    // only change bg when the property is ground
    if(e == ground){
        for(int i = place.x; i < place.x + place.w; i++){
            for(int j = place.y; j < place.y + place.h; j++){
                bg[i][j] = e;
            }
        }   
    }

    // check input is valid
    if(direction == L_and_R){
        // start <= PosX <= end
        if(PosX < start){
            cout << "start point " << start << \
                " must smaller than PosX: " << PosX << endl;
            cout << "fail to generate map" << endl;
            exit(1);
        }
        else if(PosX > end){
            cout << "end point " << end << \
                " must bigger than PosX: " << PosX << endl;
            cout << "fail to generate map" << endl;
            exit(1);
        }                
    }
    if(direction == U_and_D){
        // start <= PosY <= end
        if(PosY < start){
            cout << "start point " << start << \
                " must smaller than PosY: " << PosY << endl;
            cout << "fail to generate map" << endl;
            exit(1);
        }
        else if(PosY > end){
            cout << "end point " << end << \
                " must bigger than PosY: " << PosY << endl;
            cout << "fail to generate map" << endl;
            exit(1);
        }    
    }
}


void object::change_type(int e, int** bg){
    _event = e;
    // only change bg when the property is ground
    if(e == ground){
        for(int i = place.x; i < place.x + place.w; i++){
            for(int j = place.y; j < place.y + place.h; j++){
                bg[i][j] = e;
            }
        }   
    }
}


void object::change_img(SDL_Renderer* gRenderer, string img_path){
    SDL_DestroyTexture(picture);
    if(img_path != "")
        picture = LoadTexture(gRenderer, img_path);
}


// notice that if direction == None, the object will not move
void object::move(int** bg, character* person){
    /* 
    TODO: check when going through character
    this might lead to some bug
    */

    // move
    if(_direction == L_and_R){
        if(_v > 0){
            // from start to end
            if(place.x < _end){
                // notice that place.x + place.w should not > the boundary
                // which means the object should not going out of the map
                for(int i = place.y; i < place.y + place.h; i++){
                    bg[place.x][i] = empty;
                    bg[place.x + place.w][i] = _event;
                }
                place.x = place.x + _v;  
            }
            else{
                _v = -_v;
            }
        }
        else{
            // from end to start
            if(place.x > _start){
                // notice that place.x - 1 should not < the boundary
                // which means the object should not going out of the map
                for(int i = place.y; i < place.y + place.h; i++){
                    bg[place.x + place.w - 1][i] = empty;
                    bg[place.x - 1][i] = _event;
                }
                place.x = place.x + _v;
            }
            else{
                _v = -_v;
            }
        }
    }

    if(_direction == U_and_D){
        if(_v > 0){
            // from start to end
            if(place.y < _end){
                // the object should not going out of the map
                for(int i = place.x; i < place.x + place.w; i++){
                    bg[i][place.y] = empty;
                    bg[i][place.y + place.h] = _event;
                }
                place.y = place.y + _v;
            }
            else{
                _v = -_v;
            }
        }
        else{
            // from end to start
            if(place.y > _start){
                // the object should not going out of the map
                for(int i = place.x; i < place.x + place.w; i++){
                    bg[i][place.y + place.h - 1] = empty;
                    bg[i][place.y - 1] = _event;
                }
                place.y = place.y + _v;

                // check if the object touch the character
                // place.y ==  person.place.y + person.place.w
                int front = person->place.x;
                int back = person->place.x + person->place.w;
                if(
                    (
                        front > place.x && front < place.x + place.w ||\
                        back > place.x && back < place.x + place.w
                    ) && person->place.y < place.y
                ){
                    if(person->place.y + person->place.h >= place.y)
                        person->place.y = person->place.y + _v;
                }  
            }
            else{
                _v = -_v;
            }
        }
    }
}

// customized function, design how your monster move here
void object::move_monster(int**bg, character* person){
    int _v = 1;
    if(_direction == Monster){
        place.x = place.x - _v;
        // stop monster when it goes out from the window
        if(place.x <= -100)
            _event = empty;
        
        int move_y = obj_up_v;
        if(place.x > 0){
            if(check_top(bg))
                move_y = move_y + person->get_vy();

            while(move_y != 0){
                if(move_y > 0){
                    // go down
                    if(!check_ground(bg)){
                        place.y = place.y + 1;
                        move_y = move_y - 1;
                    }
                    else
                        move_y = 0;   
                }
                else{
                    // go up
                    if(check_top(bg)){
                        place.y = place.y - 1;
                        move_y = move_y + 1;
                    }
                    else
                        move_y = 0;
                }
            }
        }
    }
}


bool object::check_ground(int** bg){
    for(int i = place.x; i < place.x + place.w; i++){
        if(bg[i][place.y + place.w] != ground)
            return false;
    }
    return true;
}


bool object::check_top(int** bg){
    for(int i = place.x; i < place.x + place.w; i++){
        if(bg[i][place.y - 1] != empty)
            return false;
    }
    return true;
}


void object::render(SDL_Renderer* gRenderer, SDL_Rect* camera){
    if(_event != invisible){
        SDL_Rect show = this->place;
        show.x = this->place.x - camera->x;
        show.y = this->place.y - camera->y;
        SDL_RenderCopyEx(gRenderer, picture, NULL, &show, 0.0, NULL, SDL_FLIP_NONE);
    }
}


int object::check_collision(character* person){
    const SDL_Rect p1 = place;
    const SDL_Rect p2 = person->place;
    if(SDL_HasIntersection(&p1, &p2)){
        return _event;
    }
    return empty;
}


// def how activate object here
void handel_event(m_st_ob& list, string name, int event, int** bg, SDL_Renderer* gRenderer){
    
    m_st_ob::iterator itr;
    itr = list.find(name);
    
    switch(event){
        case invisible:
            itr->second.change_type(ground, bg);            
            break;

        case event1:
            itr->second.change_type(ground, bg);
            itr->second.change_img(gRenderer, "source/picture/background/stand.png");
            itr = list.find("event1-a");
            itr->second.change_type(ground, bg);
            break;

        case event2:
            itr->second.change_type(empty, bg);
            itr->second.change_img(gRenderer, "source/picture/background/event2-a.png");
            itr = list.find("event2-a");
            itr->second.change_direction(U_and_D);
            break;

        case event3:
            itr->second.change_type(empty, bg);
            itr->second.change_img(gRenderer, "");
            itr = list.find("event3-a");
            itr->second.change_type(win, bg);
            break;

        case event4:
            itr->second.change_type(empty, bg);
            itr = list.find("event4-a");
            itr->second.change_type(ground, bg);
            itr->second.change_img(gRenderer, "source/picture/background/event4.png");
            itr = list.find("event4-b");
            itr->second.change_direction(Monster);
            break;

        case win:
            break;

        case monster:
        case dead:
            break;

        default:
            cout << "Unknown event: " << itr->first << " " <<itr->second.get_event() << endl;
            break;
    }

    return;
}