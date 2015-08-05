#include "SDLState.h"
#include <iostream>
SDLState::SDLState()
{
	int res = SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_VIDEO |
		SDL_INIT_EVENTS
		);
	if(res != 0) {
		std::cerr << SDL_GetError() << std::endl;
	}
}

SDLState::~SDLState()
{
	SDL_Quit();
}
