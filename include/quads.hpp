#ifndef QUADS_HPP
#define QUADS_HPP
#include "opengl_util.hpp"
#include <vector>
struct Vertex3 {
	static const unsigned PositionComponents = 3;
	static const unsigned TextureComponents = 2;
	static const unsigned TotalComponents = PositionComponents + TextureComponents;
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
public:
	typedef unsigned short IndexType;
	static const GLuint IndexTypeID = GL_UNSIGNED_SHORT;

	typedef Vertex3 VertexType;

	typedef glm::mat4 MatrixType;

private:
	std::vector<VertexType> vertices;
	std::vector<IndexType> indices;
	std::vector<MatrixType> transforms;
public:

	// Appends a real quad to the vertex list.
	// Returns Quad ID.
	RealQuadID addVertex(Quad);

	// Appends an indexed quad to the index list.
	// The input quadID must be the ID of an existing concrete quad in the list.
	// returns the quad number.
	IndexedQuadID addIndex(RealQuadID quadID);

	unsigned vertexDataCount() const;
	unsigned indexDataCount() const;
	unsigned transformDataCount() const;

	unsigned vertexDataByteCount() const;
	unsigned indexDataByteCount() const;
	unsigned transformDataByteCount() const;

	const VertexType * vertexData() const;
	const IndexType * indexData() const;
	const MatrixType * transformData() const;

	// Bind and upload vertex/index/matrix data
	void uploadVertices(GLuint buf) const;
	void uploadIndices(GLuint buf) const;
	void uploadTransforms(GLuint buf) const;

	// Sets up vbo data interpretation.
	void setupVertexFormat(GLuint buf, GLuint location) const;
	void setupTextureCoordinateFormat(GLuint buf, GLuint location) const;
	void setupTransformFormat(GLuint buf, GLuint location) const;


	MatrixType & transform(IndexedQuadID);

	void draw(GLuint ebo) const;
};

#endif
