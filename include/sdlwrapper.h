// Wrapper for SDL.
// Uses destructor to clean-up so you don't have to.
#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H
#include "SDL2/SDL.h"

class SDLState{
public:
	SDLState();
	~SDLState();
};

class SDLVideoSystem {
	bool good;
public:
	SDLVideoSystem();
	~SDLVideoSystem();
	bool isGood() const;
};

class SDLWindow {
	SDL_Window * data;
public:
	SDLWindow(const SDLVideoSystem&,
		char const* name,
		int x,
		int y,
		int w,
		int h,
		unsigned flags);
	~SDLWindow();

	bool isGood() const;

	SDL_Window* ptr();
};

class SDLRenderer {
	SDL_Renderer * data;
public:
	SDLRenderer(SDLWindow &,
		int index,
		unsigned flags);

	~SDLRenderer();

	bool isGood() const;

	SDL_Renderer* ptr();
	
};




#endif
