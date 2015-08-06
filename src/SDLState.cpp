#include "SDLState.h"
#include <iostream>

SDLRenderer::SDLRenderer()
{
	data = 0;
}
SDLRenderer::SDLRenderer(SDL_Window * window,
		int index,
		unsigned flags)
{
	data = SDL_CreateRenderer(window, index, flags);
	if(data == 0) {
		std::cerr << SDL_GetError() << std::endl;
	}
}
SDLRenderer::SDLRenderer(SDLRenderer&& r)
{
	data = r.data;
	r.data = 0;
}
SDLRenderer::~SDLRenderer()
{
	if(data != 0) {
		SDL_DestroyRenderer(data);
		data = 0;
	}
}

const SDLRenderer&
SDLRenderer::operator=(SDLRenderer&& r)
{
	if(data != 0) {
		SDL_DestroyRenderer(data);
	}
	data = r.data;
	r.data = 0;
	return *this;
}

bool SDLRenderer::isGood() const
{
	return data != 0;
}

SDL_Renderer* SDLRenderer::ptr()
{
	return data;
}
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
