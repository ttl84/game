#include "opengl_util.hpp"
#include "file_util.hpp"
#include <memory>
#include <utility>
namespace gl{

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
		throw Exception("init shader: failed to create shader");
	}

	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	GLint compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

	if(compiled != GL_TRUE) {
		std::string logStr = getShaderLog(id);
		throw Exception(logStr.c_str());
	}
}

void shaderFromFile(GLuint & id, GLenum shaderType, char const * path)
{
	std::string file;
	if(stringFromFile(file, path)) {
		try{
			shaderFromString(id, shaderType, file.c_str());
		} catch(const Exception & e) {
			std::string msg("in ");
			msg += path;
			msg += ": \n";
			msg += e.what();
			throw Exception(msg);
		}
	} else {
		std::string msg("failed to open shader file: ");
		msg += path;

		throw Exception(msg);
	}
}

void programFromShaders(GLuint & programID, const std::vector<GLuint> & shaders)
{
	programID = glCreateProgram();
	if(programID == 0) {
		throw Exception("init program: failed to create shader program");
	}

	for(GLuint shaderId : shaders) {
		glAttachShader(programID, shaderId);
	}

	glLinkProgram(programID);

	GLint linked;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if(linked != GL_TRUE) {
		std::string logStr = getProgramLog(programID);
		throw Exception(logStr.c_str());
	}
}


// Shader helper class
class Shader{
	GLuint id;
public:
	Shader()
	{
		id = 0;
	}
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader && s)
	{
		*this = std::move(s);
	}
	Shader& operator=(Shader&& s)
	{
		if(id != 0) {
			glDeleteShader(id);
		}
		id = s.id;
		s.id = 0;

		return *this;
	}
	static Shader fromString(GLenum shaderType, GLchar const * source)
	{
		Shader s;
		shaderFromString(s.id, shaderType, source);
		return std::move(s);
	}
	static Shader fromFile(GLenum shaderType, char const * path)
	{
		Shader s;
		shaderFromFile(s.id, shaderType, path);
		return std::move(s);
	}
	~Shader()
	{
		if(id != 0) {
			glDeleteShader(id);
		}
	}

	GLuint getID() const
	{
		return id;
	}
};

void programFromShaderFiles(GLuint& programID,
	const std::vector<std::pair<GLenum, char const*>>& sources)
{
	std::vector<Shader> shaders;
	for(auto p : sources) {
		GLenum shaderType = p.first;
		char const * path = p.second;
		shaders.push_back(Shader::fromFile(shaderType, path));
	}

	std::vector<GLuint> shaderIds;
	for(Shader & s : shaders) {
		shaderIds.push_back(s.getID());
	}

	programFromShaders(programID, shaderIds);
}

Program::Program(const std::vector<std::pair<GLenum, char const*>>& sources)
{
	id = 0;
	programFromShaderFiles(id, sources);
}
Program::~Program()
{
	if(id != 0) {
		glDeleteProgram(id);
		id = 0;
	}
}
void Program::use() const
{
	glUseProgram(id);
}

Texture2D::Texture2D(unsigned width, unsigned height, uint8_t * const data)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
Texture2D::~Texture2D()
{
	glDeleteTextures(1, &id);
}

void Texture2D::bind()const
{
	glBindTexture(GL_TEXTURE_2D, id);
}
void Texture2D::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
} // end namespace gl
