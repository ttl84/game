// Wrapper for SDL.
// Uses destructor to clean-up so you don't have to.
#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H
#include "SDL2/SDL.h"
#include <map>

class SDLState{
public:
	SDLState();
	~SDLState();
};

// This class initializes both
// SDL's Video subsystem and
// the SDL_Image library
class SDLVideoSystem {
	bool videoGood;
	bool imgGood;
public:
	SDLVideoSystem();
	~SDLVideoSystem();
	bool isGood() const;
};

class SDLWindow {
	SDL_Window * data;
public:
	SDLWindow(
		SDLVideoSystem&,
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
	std::map<std::string, SDL_Texture*> textures;
public:
	SDLRenderer(
		SDLWindow &,
		int index,
		unsigned flags);

	~SDLRenderer();

	bool isGood() const;

	SDL_Renderer* ptr();
	
	// create a texture.
	// The renderer is responsible for allocating and freeing memory.
	SDL_Texture * load(char const * name);
	void unload(char const * name);
};



#endif
