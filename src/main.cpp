#include <iostream>
#include "SDL2/SDL.h"

#include "gl/glew.h"

#include "SDL2/SDL_opengl.h"

#include <gl\glu.h>
//Screen Dimension Constants
const int win_w = 640;
const int win_h = 480;
constexpr float dt = 0.001f;


int main(int argc, char** args)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

	bool running = true;
	while(running){
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				running = false;
		}
	}
	SDL_Quit();
	return 0;
}
