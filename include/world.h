#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Vec2.h"

struct SDL_Texture;

struct Movable{
	Vec2 pos;
	Vec2 vel;
	Vec2 accel;
	Vec2 size;
	SDL_Texture * img;
};
struct World {
	std::vector<Movable> movable;
};
#endif
