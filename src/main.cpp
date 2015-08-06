#include "sdlwrapper.h"
#include <iostream>

//Screen Dimension Constants
const int win_w = 640;
const int win_h = 480;

int main(int argc, char** args){
	SDLState sdl;
	SDLVideoSystem video;
	SDLWindow window(
		video,
		"game", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		win_h, win_h,
		0   // 0 means no flags
		);
	SDLRenderer renderer(
		window,
		-1, // -1 means to init the first driver that supports the flags
		0   // 0 means no flags
		);

	bool running = true;
	while(running){
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				running = false;
		}

	}
	return 0;
}
