#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#include "./character.h"

enum{
    None,
    U_and_D,
    L_and_R,
    Monster
};


class object{
public:
    // basic object - static
    object(
        int** bg,
        int PosX,
        int PosY,
        int WIDTH,
        int HEIGHT,
        int event,
        string img_path,
        SDL_Renderer*
    );

    // basic object - moving
    object(
        int** bg,
        int PosX,
        int PosY,
        int WIDTH,
        int HEIGHT,
        int start,
        int end,
        int event,
        int direction,
        string img_path,
        SDL_Renderer*
    );

    ~object(){}

    void destroy(){SDL_DestroyTexture(picture);}

    void move(int**, character*);
    void move_monster(int**, character*);
    void render(SDL_Renderer*, SDL_Rect*);
    int check_collision(character*);
    bool check_ground(int**);
    bool check_top(int**);

    int get_event(){return _event;}
    void set_event(int e){_event = e;}
    void change_type(int, int**);
    void change_img(SDL_Renderer*, string);
    void change_direction(int d){_direction = d;}

private:
    SDL_Rect place;
	SDL_Texture* picture;
    int _v, _direction, _event;
    int _start, _end;
};

typedef pair<string, object> st_ob;
typedef map<string, object> m_st_ob;


void handel_event(m_st_ob&, string, int , int**, SDL_Renderer*);


class Map{
public:
    Map(int** bg_array, SDL_Renderer* gRenderer){
        bg = bg_array;
        _gRenderer = gRenderer;
    }

    // add static object
    void add_object(
        int PosX,
        int PosY,
        int WIDTH,
        int HEIGHT,
        int event,
        string img_path
    ){  
        cout << "_______" << endl;
        object new_object(bg, PosX, PosY, WIDTH, HEIGHT, event, img_path, _gRenderer);
        object_list.push_back(new_object);
    }

    // add moving object
    void add_object(
        int PosX,
        int PosY,
        int WIDTH,
        int HEIGHT,
        int start,
        int end,
        int event,
        int direction,
        string img_path
    ){
        cout << "_______" << endl;
        object new_object(bg, PosX, PosY, WIDTH, HEIGHT, start, end, event, direction, img_path, _gRenderer);
        moving_object_list.push_back(new_object);
    }

    // add active object
    void add_object(
        string name,
        int PosX,
        int PosY,
        int WIDTH,
        int HEIGHT,
        int start,
        int end,
        int event,
        int direction,
        string img_path
    ){
        cout << "_______" << endl;
        cout << name << endl;
        object new_object(bg, PosX, PosY, WIDTH, HEIGHT, start, end, event, direction, img_path, _gRenderer);
        active_object_list.insert(st_ob(name, new_object));
    }

    void move(int** bg, character* person){
        for(int i = 0; i < moving_object_list.size(); i++){
            moving_object_list[i].move(bg, person);
        }

        m_st_ob::iterator itr = active_object_list.begin();
        for(itr; itr != active_object_list.end(); itr++){
            if(itr->second.get_event() == ground)
                itr->second.move(bg, person);
            else if(itr->second.get_event() == monster)
                itr->second.move_monster(bg, person);
        }
    }

    void render(SDL_Rect* camera){
        for(int i = 0; i < object_list.size(); i++){
            object_list[i].render(_gRenderer, camera);
        }
        for(int i = 0; i < moving_object_list.size(); i++){
            moving_object_list[i].render(_gRenderer, camera);
        }
        m_st_ob::iterator itr = active_object_list.begin();
        for(itr; itr != active_object_list.end(); itr++){
            itr->second.render(_gRenderer, camera);
        }
    }

    int check_event(character* person){
        m_st_ob::iterator itr = active_object_list.begin();
        for(itr; itr != active_object_list.end(); itr++){
            int event = itr->second.check_collision(person);
            if(event != empty && event != ground){
                handel_event(active_object_list, itr->first, event, bg, _gRenderer);
            }
            if(event == monster || event == dead){
                return dead;
            }
            if(event == win){
                return win;
            }
        }
        return empty;
    }

    void clean(){
        for(int i = 0; i < object_list.size(); i++){
            object_list[i].destroy();
        }
        for(int i = 0; i < moving_object_list.size(); i++){
            moving_object_list[i].destroy();
        }
        m_st_ob::iterator itr = active_object_list.begin();
        for(itr; itr != active_object_list.end(); itr++){
            itr->second.destroy();
        }
    }

    // basic object, which will not change property
    vector<object> object_list; 
    vector<object> moving_object_list;

    // active object, which will change property by the character
    m_st_ob active_object_list;

    int** bg;
    SDL_Renderer* _gRenderer;
};
#endif

     