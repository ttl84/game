#include "quads.hpp"
#include <cstddef> // for offsetof
RealQuadID vertexNumberToRealQuadID(unsigned i)
{
	return RealQuadID{i / 4};
}
unsigned realQuadIDToVertexNumber(RealQuadID id)
{
	return id.value * 4;
}
IndexedQuadID indexNumberToIndexedQuadID(unsigned i)
{
	return IndexedQuadID{i / 6};
}

RealQuadID Quads::addVertex(Quad q)
{
	RealQuadID id = vertexNumberToRealQuadID(vertices.size());
	vertices.insert(
		vertices.end(),
		std::begin(q.vertex),
		std::end(q.vertex));
	return id;
}

IndexedQuadID Quads::addIndex(RealQuadID realID)
{
	unsigned i = realQuadIDToVertexNumber(realID);
	unsigned elements [] = {
		i+0, i+1, i+3,
		i+1, i+2, i+3
	};

	IndexedQuadID id = indexNumberToIndexedQuadID(indices.size());
	indices.insert(
		indices.end(),
		std::begin(elements),
		std::end(elements));
	Quads::MatrixType mat;
	transforms.push_back(mat);
	return id;
}

unsigned Quads::vertexDataCount() const
{
	return vertices.size();
}

unsigned Quads::indexDataCount() const
{
	return indices.size();
}

unsigned Quads::transformDataCount() const
{
	return transforms.size();
}

unsigned Quads::vertexDataByteCount() const
{
	return vertices.size() * sizeof(Quads::VertexType);
}

unsigned Quads::indexDataByteCount() const
{
	return indices.size() * sizeof(Quads::IndexType);
}

unsigned Quads::transformDataByteCount() const
{
	return transforms.size() * sizeof(Quads::MatrixType);
}

const Quads::VertexType * Quads::vertexData() const
{
	return vertices.data();
}

const Quads::IndexType * Quads::indexData() const
{
	return indices.data();
}

const Quads::MatrixType * Quads::transformData() const
{
	return transforms.data();
}

void Quads::uploadVertices(GLuint vbo) const
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertexDataByteCount(),
		vertexData(),
		GL_STATIC_DRAW);
}

void Quads::uploadIndices(GLuint ebo) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indexDataByteCount(),
		indexData(),
		GL_STATIC_DRAW);
}

void Quads::uploadTransforms(GLuint mbo) const
{
	glBindBuffer(GL_ARRAY_BUFFER, mbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		transformDataByteCount(),
		transformData(),
		GL_STATIC_DRAW
	);
}

void Quads::setupVertexFormat(GLuint buf, GLuint location) const
{
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glVertexAttribPointer(
		location,
		Quads::VertexType::PositionComponents,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Quads::VertexType),
		(GLvoid*)0
	);
	glEnableVertexAttribArray(location);
}

void Quads::setupTextureCoordinateFormat(GLuint buf, GLuint location) const
{
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glVertexAttribPointer(
			location,
			Quads::VertexType::TextureComponents,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Quads::VertexType),
			(GLvoid*) offsetof(Quads::VertexType, texture)
		);
	glEnableVertexAttribArray(location);
}

void Quads::setupTransformFormat(GLuint buf, GLuint location) const
{
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	for(unsigned i = 0; i < 4; i++) {
		glVertexAttribPointer(
			location + i,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Quads::MatrixType),
			(GLvoid*) (i * sizeof(glm::vec4))
		);
		glEnableVertexAttribArray(location + i);
		glVertexAttribDivisor(location + i, 1);
	}
}

Quads::MatrixType & Quads::transform(IndexedQuadID id)
{
	return transforms[id.value];
}

void Quads::draw(GLuint ebo) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElementsInstanced(
		GL_TRIANGLES,
		indexDataCount(),
		Quads::IndexTypeID,
		0,
		transformDataCount()
	);
}