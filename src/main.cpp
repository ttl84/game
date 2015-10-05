#include "sdlwrapper.hpp"
#include "gl/glew.h"
#include "SDL2/SDL_opengl.h"
#include "gl/glu.h"

#include <iostream>
#include <string>
#include <exception>
#include <memory>

class Exception : public std::exception {
  std::string message;
public:
  Exception(char const* msg)
    : message(msg)
  {
  }
  virtual char const* what() noexcept
  {
    return message.c_str();
  }
};

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

void init_shader(GLuint & id, GLenum shaderType, GLchar const* source)
{
  id = glCreateShader(shaderType);
  if(id == 0) {
    throw Exception("init shader: failed to create shader");
  }

  glShaderSource(id, 1, &source, NULL);
  if(glGetError()) {
    throw Exception("init shader: unexpected error");
  }

  glCompileShader(id);
  if(glGetError()) {
    throw Exception("init shader: unexpected error");
  }

  GLint compiled;
  glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

  if(compiled != GL_TRUE) {
    std::string logStr = get_shader_log(id);
    if(logStr.length() != 0) {
      throw Exception(logStr.c_str());
    }
  }
}

void init_vertex_shader(GLuint & id, GLchar const * source)
{
  init_shader(id, GL_VERTEX_SHADER, source);
}
void init_fragment_shader(GLuint & id, GLchar const * source)
{
  init_shader(id, GL_FRAGMENT_SHADER, source);
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

int main(int argc, char** args)
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
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

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

	// clear colour
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // vertex shader
  GLuint vertexShaderId;
  GLchar const * vertexShaderSource =
    "#version 330 core"
    "layout (location = 0) in vec3 position;"
    "void main()"
    "{"
    "    gl_Position = vec4(position.x, position.y, position.z, 1.0);"
    "}"
  ;
  init_vertex_shader(vertexShaderId, vertexShaderSource);

  // fragment shader
  GLuint fragmentShaderId;
  GLchar const* fragmentShaderSource =
    "#version 330 core"
    "out vec4 color;"
    "void main()"
    "{"
    "    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}"
  ;
  init_fragment_shader(fragmentShaderId, fragmentShaderSource);

  // vertex data
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	bool running = true;
	while(running){
		for(SDL_Event e : sdlEvents) {
			if(e.type == SDL_QUIT)
				running = false;
		}

		// render
		glClear(GL_COLOR_BUFFER_BIT);

		//Update screen
		SDL_GL_SwapWindow( window.get() );
	}

	return 0;
}
