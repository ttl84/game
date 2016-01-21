#include "quads.hpp"
#include <cstddef> // for offsetof

Quads::Quads()
{
	glGenBuffers(1, &vertexAndTextureBuf);
	glGenBuffers(1, &transformBuf);
	glGenBuffers(1, &indexBuf);
}

RealQuadID vertexNumberToRealQuadID(unsigned i)
{
	return RealQuadID{i / TexturedQuad::QUAD_COMPONENTS};
}
unsigned realQuadIDToVertexNumber(RealQuadID id)
{
	return id.value * TexturedQuad::QUAD_COMPONENTS;
}
IndexedQuadID indexNumberToIndexedQuadID(unsigned i)
{
	return IndexedQuadID{i / Quads::INDEX_QUAD_COMPONENTS};
}

RealQuadID Quads::addVertex(TexturedQuad q)
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
	assert(id.value == transforms.size() - 1);
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

void Quads::uploadVertices() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexAndTextureBuf);
	glBufferData(
				GL_ARRAY_BUFFER,
				vertexDataByteCount(),
				vertexData(),
				GL_STATIC_DRAW);
}

void Quads::uploadIndices() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
	glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				indexDataByteCount(),
				indexData(),
				GL_STATIC_DRAW);
}

void Quads::uploadTransforms() const
{
	glBindBuffer(GL_ARRAY_BUFFER, transformBuf);
	glBufferData(
				GL_ARRAY_BUFFER,
				transformDataByteCount(),
				transformData(),
				GL_STATIC_DRAW
				);
}

void Quads::setupVertexFormat(GLuint location) const
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexAndTextureBuf);
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

void Quads::setupTextureCoordinateFormat(GLuint location) const
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexAndTextureBuf);
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

void Quads::setupTransformFormat(GLuint location) const
{
	glBindBuffer(GL_ARRAY_BUFFER, transformBuf);
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

void Quads::draw() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
	glDrawElementsInstanced(
				GL_TRIANGLES,
				indexDataCount(),
				Quads::IndexTypeID,
				0,
				transformDataCount()
				);
}
