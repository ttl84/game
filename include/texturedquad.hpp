#ifndef TEXTUREDQUAD_HPP
#define TEXTUREDQUAD_HPP
#include "opengl_util.hpp"
struct Vertex3 {
	static const unsigned POSITION_COMPONENTS = 3;
	static const unsigned TEXTURE_COORDINATE_COMPONENTS = 2;
	GLfloat position[3];
	GLfloat texture[2];
};

struct TexturedQuad {
	static const unsigned QUAD_COMPONENTS = 4;
	Vertex3 vertex[QUAD_COMPONENTS];
};
#endif // TEXTUREDQUAD_HPP
