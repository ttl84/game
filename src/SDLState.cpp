#include "SDLState.h"
#include <iostream>

SDLWindow::SDLWindow(char const* name,
		int x,
		int y,
		int w,
		int h,
		unsigned flags)
{
	data = SDL_CreateWindow(name, x, y, w, h, flags);
	if(data == 0) {
		std::cerr << SDL_GetError() << std::endl;
	}
}

SDLWindow::~SDLWindow()
{
	if(data != 0) {
		SDL_DestroyWindow(data);
		data = 0;
	}
}

bool SDLWindow::isGood() const
{
	return data != 0;
}

SDL_Window* SDLWindow::ptr()
{
	return data;
}

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
