#ifndef OPENGL_UTIL_HPP
#define OPENGL_UTIL_HPP
#include "GL/glew.h"
#include <string>
#include <vector>
#include <exception>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace gl{
class Exception : public std::exception{
	std::string msg;

public:
	explicit Exception(char const * s) : msg(s){}
	explicit Exception(std::string const & s) :msg(s){}

	virtual char const * what() const noexcept
	{
		return msg.c_str();
	}
};

// Get the log of a shader program
std::string getProgramLog(GLuint id);

// Get the log of a shader
std::string getShaderLog(GLuint id);

// Create shader objects.
// Shader id will be assigned to id after function is finished.
// If the shader source doesn't compile, an exception will be thrown.
void shaderFromString(GLuint & id, GLenum shaderType, GLchar const* source);
void shaderFromFile(GLuint & id, GLenum shaderType, char const* source);

// Create shader program.
// Program id will be assigned to id after function is finished.
// If the program doesn't link, an exception will be thrown.
void programFromShaders(GLuint & programID, const std::vector<GLuint> & shaders);
void programFromShaderFiles(GLuint& programID,
	const std::vector<std::pair<GLenum, char const*>>& sources);


class Program {
public:
	GLuint id;
	Program(const std::vector<std::pair<GLenum, char const*>>& sources);
	~Program();
	Program(const Program& other) = delete;
	Program & operator=(const Program& other) = delete;

	void use() const;
};

// Wrapper for 2D RGBA unsigned byte textures.
class Texture2D {
	GLuint id;
public:

	// Create a texture with data.
	// The data must be arranged like so:
	// RGBARGBARGBA...
	Texture2D(unsigned width, unsigned height, uint8_t const * data);
	~Texture2D();
	void bind() const;
	void unbind() const;
};
} // end namespace gl
#endif
