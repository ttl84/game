//Include SDL functions and datatypes
#include "SDL2/SDL.h"
#include <iostream>

//Screen Dimension Constants
const int win_w = 640;
const int win_h = 480;

int main(int argc, char** args){
	SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * window = NULL;
    SDL_Renderer* renderer = NULL;

    window = SDL_CreateWindow( "game", 
    	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    		win_h, win_h, 0);
    while(1){

    }
    SDL_Quit();
	return 0;
}
