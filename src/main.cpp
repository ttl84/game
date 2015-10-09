#include "sdlwrapper.hpp"
#include "gl/glew.h"
#include "SDL2/SDL_opengl.h"
#include "gl/glu.h"

#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>

std::string get_shader_log(GLuint id)
{
	GLint logMaxLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logMaxLength);
	std::unique_ptr<GLchar[]> logBuf(new GLchar[logMaxLength]);

	GLsizei logLength;
	glGetShaderInfoLog(id, logMaxLength, &logLength, logBuf.get());

	std::string logStr(logBuf.get());

	return logStr;
}

std::string get_program_log(GLuint id)
{
	GLint logMaxLength;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logMaxLength);
	std::unique_ptr<GLchar[]> logBuf(new GLchar[logMaxLength]);

	GLsizei logLength;
	glGetProgramInfoLog(id, logMaxLength, &logLength, logBuf.get());

	std::string logStr(logBuf.get());

	return logStr;
}

void shaderFromString(GLuint & id, GLenum shaderType, GLchar const* source)
{
	id = glCreateShader(shaderType);
	if(id == 0) {
		throw sdl2::Exception("init shader: failed to create shader");
	}

	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	GLint compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

	if(compiled != GL_TRUE) {
		std::string logStr = get_shader_log(id);
		throw sdl2::Exception(logStr.c_str());
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

void init_program(GLuint & programID, const std::vector<GLuint> & shaders)
{
	programID = glCreateProgram();
	if(programID == 0) {
		throw sdl2::Exception("init program: failed to create shader program");
	}

	for(GLuint shaderId : shaders) {
		glAttachShader(programID, shaderId);
	}

	glLinkProgram(programID);

	GLint linked;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if(linked != GL_TRUE) {
		std::string logStr = get_program_log(programID);
		throw sdl2::Exception(logStr.c_str());
	}
}
int init_SDL_GL()
{
	//Use OpenGL 3.3 core
	int err;

	err = SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	if(err) return -1;

	err = SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	if(err) return -1;

	err = SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	if(err) return -1;

	return 0;
}
int run()
{
	unsigned win_w = 640;
	unsigned win_h = 640;
	sdl2::SDL sdl;
	sdl2::VideoSystem sdlVideo;
	sdl2::EventSystem sdlEvents;
	int result;

	result = init_SDL_GL();
	if(result != 0) {
		std::cout << SDL_GetError() << '\n';
		return -1;
	}

	//Create window
	sdl2::Window window(
		"game",
		win_w, win_h,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	//Create context
	sdl2::GLContext glContext(window);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK ) {
		std::cout << glewGetErrorString( glewError );
		return -1;
	}

	//Use Vsync
	if( SDL_GL_SetSwapInterval(1) < 0 ) {
		std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << '\n';
	}

	// camera
	glViewport(0, 0, win_w, win_h);




	// shader program
	GLuint vertexShaderId;
	GLchar const * vertexShaderSource =
	"#version 330 core\n"
	"layout(location = 0) in vec3 inPosition;"
	//"out vec4 outPosition;"
	"void main()"
	"{"
	"	gl_Position.xyz = inPosition;"
	"	gl_Position.w = 1.0;"
	"}"
	;
	vertexShaderFromString(vertexShaderId, vertexShaderSource);

	GLuint fragmentShaderId;
	GLchar const* fragmentShaderSource =
	"#version 330 core\n"
	"layout(location = 0) out vec4 color;"
	"void main()"
	"{"
	"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
	"}"
	;
	fragmentShaderFromString(fragmentShaderId, fragmentShaderSource);

	std::vector<GLuint> shaders = {vertexShaderId, fragmentShaderId};
	GLuint programID;
	init_program(programID, shaders);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	// vertex data
	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	bool running = true;
	while(running){
		for(SDL_Event e : sdlEvents) {
			if(e.type == SDL_QUIT)
			running = false;
		}

		// render

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID);
		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//Update screen
		SDL_GL_SwapWindow( window.get() );
	}
	return 0;
}
int main(int argc, char** args)
{
	try {
		run();
	} catch(sdl2::Exception & e) {
		std::cout << e.what() << '\n';
	}
	return 0;
}
