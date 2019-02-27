# 2D-Side-scrolling-Game
Using c++ to make a simple 2D Side-scrolling Game by yourself
The picture and sound is quite big, so be patient when downloading.

## Demo (It might be lag for playing the first time)
![image](https://github.com/harry1003/-Utility/blob/master/2d_game_demo.gif)

## Environment
This project is developed on Linux. So if you use windows, you  
might need to compile c++ files by yourself.

## Set up
1. For linux, run below in your terminal

	    sudo apt-get install libsdl2-dev
	    sudo apt-get install libsdl2-image-dev
	    sudo apt-get install libsdl2-mixer-dev

2. For Windows, you should install

        sdl2
        sdl2-mixer
        sdl2-image
    see https://www.libsdl.org/download-2.0.php for more detail

## How to use this code?
### 1. For someone who just want to playing the game

        cd ./game
        ./game_linux

### 2. For someone who want to create your own map
* You may see "./map/level1.cpp" for example first.
* To build a map, you just need to define object in the map.
* There are some property you can use:
    * empty: just put a picture there
    * ground: place where is solid. character can't go through.
    * invisible: can only be seem after character touch it
    * move object: object that can move
* To define a customized event, you should:
    1. define this event in ./util.h -> enum{}
    2. define what this event actually done in object.cpp

### 3. For someone who want to know how this works

    /*Todo*/

## How to comile this file after I change it?
Just type below in ./game (for linux)

    make
---
advises and pull requests are welcome
