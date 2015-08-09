#include "sdlwrapper.h"
#include <iostream>
#include "world.h"
//Screen Dimension Constants
const int win_w = 640;
const int win_h = 480;
constexpr float dt = 0.001f;

void update(World & w, float dt)
{
}
void draw(SDLRenderer& r, World& w)
{
	for(auto & obj : w.movable) {
		SDL_RenderCopy(r.ptr(), obj.img,
			0, 0);
	}
}
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

	World world;

	bool running = true;
	SDLTimer timer;
	while(running){
		unsigned t = timer.lap();
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				running = false;
			else if(e.type == SDL_KEYDOWN) {
				std::cout << "t=" << t << std::endl;
				//std::cout << "goal="<< goal << std::endl;
			}
		}

		if(t == 0) {
			t = 1;
		} else if(t > 30) {
			t = 30;
		}
		while(t != 0) {
			t--;
			update(world, dt);
		}

		draw(renderer, world);
	}
	return 0;
}
