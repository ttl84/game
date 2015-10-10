#include "opengl_util.hpp"
#include <memory>

std::string getProgramLog(GLuint id)
{
	GLint logMaxLength;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logMaxLength);
	std::unique_ptr<GLchar[]> logBuf(new GLchar[logMaxLength]);

	GLsizei logLength;
	glGetProgramInfoLog(id, logMaxLength, &logLength, logBuf.get());

	if(logLength != 0) {
		return std::string(logBuf.get());
	} else {
		return std::string();
	}
}

std::string getShaderLog(GLuint id)
{
	GLint logMaxLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logMaxLength);
	std::unique_ptr<GLchar[]> logBuf(new GLchar[logMaxLength]);

	GLsizei logLength;
	glGetShaderInfoLog(id, logMaxLength, &logLength, logBuf.get());

	if(logLength != 0) {
		return std::string(logBuf.get());
	} else {
		return std::string();
	}
}

void shaderFromString(GLuint & id, GLenum shaderType, GLchar const* source)
{
	id = glCreateShader(shaderType);
	if(id == 0) {
		throw gl::Exception("init shader: failed to create shader");
	}

	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	GLint compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

	if(compiled != GL_TRUE) {
		std::string logStr = getShaderLog(id);
		throw gl::Exception(logStr.c_str());
	}
}

void vertexShaderFromString(GLuint & id, GLchar const * source)
{
	shaderFromString(id, GL_VERTEX_SHADER, source);
}
void fragmentShaderFromString(GLuint & id, GLchar const * source)
{
	shaderFromString(id, GL_FRAGMENT_SHADER, source);
}

void programFromShaders(GLuint & programID, const std::vector<GLuint> & shaders)
{
	programID = glCreateProgram();
	if(programID == 0) {
		throw gl::Exception("init program: failed to create shader program");
	}

	for(GLuint shaderId : shaders) {
		glAttachShader(programID, shaderId);
	}

	glLinkProgram(programID);

	GLint linked;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if(linked != GL_TRUE) {
		std::string logStr = getProgramLog(programID);
		throw gl::Exception(logStr.c_str());
	}
}
