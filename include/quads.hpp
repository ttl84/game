#ifndef QUADS_HPP
#define QUADS_HPP
#include "opengl_util.hpp"
#include <vector>
struct Vertex3 {
	static const unsigned Components = 3;
	GLfloat position[3];
	GLfloat texture[2];
};

struct Quad {
	Vertex3 vertex[4];
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
	typedef short IndexType;
	typedef Vertex3 VertexType;
	std::vector<Vertex3> vertices;
	std::vector<IndexType> indices;
public:

	// Appends a real quad to the vertex list.
	// Returns Quad ID.
	RealQuadID addVertex(Quad);

	// Appends an indexed quad to the index list.
	// The input quadID must be the ID of an existing concrete quad in the list.
	// returns the quad number.
	IndexedQuadID addIndex(RealQuadID quadID);

	void sendVertexData(unsigned vbo) const;
	void sendIndexData(unsigned ebo) const;

	void positionVertexAttribPointer(unsigned location) const;
	void textureCoordinateVertexAttribPointer(unsigned location) const;
};

#endif
