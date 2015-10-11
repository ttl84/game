#ifndef OPENGL_UTIL_HPP
#define OPENGL_UTIL_HPP
#include "gl/glew.h"
#include <string>
#include <vector>
#include <exception>

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
	const std::vector<std::pair<GLenum, char const*>> sources);

} // end namespace gl
#endif
