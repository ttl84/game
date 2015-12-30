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

Quads::MatrixType & Quads::transform(IndexedQuadID id)
{
	return transforms[id.value];
}
