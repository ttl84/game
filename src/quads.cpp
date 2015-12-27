#include "quads.hpp"
#include <cstddef> // for offsetof
RealQuadID Quads::addVertex(Quad q)
{
	RealQuadID id = {unsigned(vertices.size()) / 4};
	vertices.insert(
		vertices.end(),
		std::begin(q.vertex),
		std::end(q.vertex));
	return id;
}

IndexedQuadID Quads::addIndex(RealQuadID realID)
{
	unsigned i = realID.value * 4;
	unsigned elements [] = {
		i+0, i+1, i+3,
		i+1, i+2, i+3
	};

	IndexedQuadID id = {unsigned(indices.size()) / 6};
	indices.insert(
		indices.end(),
		std::begin(elements),
		std::end(elements));
	return id;
}


void Quads::sendVertexData(unsigned vbo) const
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2), vertices.data(), GL_STATIC_DRAW);
}
void Quads::sendIndexData(unsigned vbo) const
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
}

void Quads::positionVertexAttribPointer(unsigned location) const
{
	glVertexAttribPointer(
		location,			// location number of vertex array
		2,					// number of components in position vector
		GL_FLOAT,			// type of vertex component
		GL_FALSE,			// normalized
		sizeof(Vertex2),	// stride
		(GLvoid*)NULL);
}

void Quads::textureCoordinateVertexAttribPointer(unsigned location) const
{
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex2),
		(GLvoid*) offsetof(Vertex2, texture));
}
