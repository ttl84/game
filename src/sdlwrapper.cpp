#include "sdlwrapper.h"
#include <iostream>
SDLState::SDLState()
{
	int res = SDL_Init(0);
	if(res != 0) {
		std::cerr << SDL_GetError() << std::endl;
	}
}

SDLState::~SDLState()
{
	SDL_Quit();
}


SDLVideoSystem::SDLVideoSystem()
{
	int res = SDL_VideoInit(0);
	if(res == 0) {
		good = true;
	} else {
		std::cerr << SDL_GetError() << std::endl;
		good = false;
	}
}
SDLVideoSystem::~SDLVideoSystem()
{
	SDL_VideoQuit();
}
bool SDLVideoSystem::isGood() const
{
	return good;
}


SDLWindow::SDLWindow(const SDLVideoSystem& video,
	char const* name,
	int x,
	int y,
	int w,
	int h,
	unsigned flags)
{
	if(video.isGood())
		data = SDL_CreateWindow(name, x, y, w, h, flags);
	else
		data = 0;
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

SDLRenderer::SDLRenderer(SDLWindow & window,
		int index,
		unsigned flags)
{
	if(window.isGood()) {
		data = SDL_CreateRenderer(
			window.ptr(),
			index,
			flags);
	} else {
		data = 0;
	}
	if(data == 0) {
		std::cerr << SDL_GetError() << std::endl;
	}
}

SDLRenderer::~SDLRenderer()
{
	if(data != 0) {
		SDL_DestroyRenderer(data);
		data = 0;
	}
}

bool SDLRenderer::isGood() const
{
	return data != 0;
}

SDL_Renderer* SDLRenderer::ptr()
{
	return data;
}

