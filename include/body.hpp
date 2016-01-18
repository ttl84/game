#ifndef BODY_HPP
#define BODY_HPP
#include "Vec2.hpp"

struct Body {
	Vec2 acceleration;
	Vec2 velocity;

	Vec2 halfSides; // half width and half height
	Vec2 position;

	Vec2 scale;
};
#endif // BODY_HPP
