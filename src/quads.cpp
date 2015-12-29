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
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Quads::VertexType),
		vertices.data(),
		GL_STATIC_DRAW);
}
void Quads::sendIndexData(unsigned vbo) const
{
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(Quads::IndexType),
		indices.data(),
		GL_STATIC_DRAW);
}

void Quads::positionVertexAttribPointer(unsigned location) const
{
	glVertexAttribPointer(
		location,			// location number of vertex array
		Quads::VertexType::PositionComponents,					// number of components in position vector
		GL_FLOAT,			// type of vertex component
		GL_FALSE,			// normalized
		sizeof(Quads),		// stride
		(GLvoid*)NULL);
}

void Quads::textureCoordinateVertexAttribPointer(unsigned location) const
{
	glVertexAttribPointer(
		location,
		Quads::VertexType::TextureComponents,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Quads::VertexType),
		(GLvoid*) offsetof(Quads::VertexType, texture));
}
