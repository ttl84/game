// Wrapper for SDL.
// Uses destructor to clean-up so you don't have to.
#ifndef SDLSTATE_H
#define SDLSTATE_H
#include "SDL2/SDL.h"
class SDLState{
public:
	SDLState();
	~SDLState();
private:
	SDLState(const SDLState &);
	const SDLState& operator=(const SDLState &);
};
#endif
