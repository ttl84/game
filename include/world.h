#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Vec2.h"
struct Movable{
	Vec2 pos;
	Vec2 vel;
	Vec2 accel;
};
class World {
	std::vector<Movable> movable;
};
#endif
