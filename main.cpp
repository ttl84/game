//Include SDL functions and datatypes
#include "SDL2/SDL.h"
#include <iostream>

//Screen Dimension Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * window = NULL;
    SDL_Renderer* renderer = NULL;

    window = SDL_CreateWindow( "SDL Tutorial", 
    	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    while(1){

    }
    SDL_Quit();
	return 0;
}
