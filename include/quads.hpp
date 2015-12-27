#ifndef QUADS_HPP
#define QUADS_HPP
#include "opengl_util.hpp"
#include <vector>
struct Vertex2 {
	GLfloat position[2];
	GLfloat texture[2];
};

struct Quad {
	Vertex2 vertex[4];
};
struct RealQuadID{
	unsigned value;
};

struct IndexedQuadID{
	unsigned value;
};

// This is a list of quads.
// Each quad must have all its vertices added consecutively.
class Quads{
	std::vector<Vertex2> vertices;
	std::vector<unsigned> indices;
public:
	// Appends a real quad to the vertex list.
	// Returns Quad ID.
	RealQuadID addVertex(Quad);

	// Appends an indexed quad to the index list.
	// The input quadID must be the ID of an existing concrete quad in the list.
	// returns the quad number.
	IndexedQuadID addIndex(RealQuadID quadID);

	void sendVertexData(unsigned vbo) const;
	void sendIndexData(unsigned vbo) const;

	void positionVertexAttribPointer(unsigned location) const;
	void textureCoordinateVertexAttribPointer(unsigned location) const;
};

#endif
