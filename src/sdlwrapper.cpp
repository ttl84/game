#include "sdlwrapper.h"
#include "SDL2/SDL_Image.h"
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
	int res1 = SDL_VideoInit(0);
	int flags = IMG_INIT_PNG;
	int res2 = IMG_Init(flags);

	if(res1 == 0) {
		videoGood = true;
	} else {
		std::cerr << SDL_GetError() << std::endl;
		videoGood = false;
	}

	if(res2 == flags) {
		imgGood = true;
	} else {
		std::cerr << "error: failed to init SDL_image\n";
		imgGood = false;
	}
}
SDLVideoSystem::~SDLVideoSystem()
{
	if(videoGood) {
		SDL_VideoQuit();
	}
	if(imgGood) {
		IMG_Quit();
	}
}
bool SDLVideoSystem::isGood() const
{
	return videoGood && imgGood;
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

SDLTexture::SDLTexture(SDLRenderer & renderer,
	char const * name)
:data(0)
{
	SDL_Surface * surface = IMG_Load(name);
	if(surface != 0) {
		data = SDL_CreateTextureFromSurface(
			renderer.ptr(), surface);
		SDL_FreeSurface(surface);
	}
}

SDLTexture::~SDLTexture()
{
	if(data != 0) {
		SDL_DestroyTexture(data);
	}
}
bool SDLTexture::isGood() const
{
	return data != 0;
}