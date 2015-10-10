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
}
// Get the log of a shader program
std::string get_program_log(GLuint id);

// Get the log of a shader
std::string get_shader_log(GLuint id);

// create shader objects
void vertexShaderFromString(GLuint & id, GLchar const * source);
void fragmentShaderFromString(GLuint & id, GLchar const * source);

void init_program(GLuint & programID, const std::vector<GLuint> & shaders);
#endif
