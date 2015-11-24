#include "sdlwrapper.hpp"
#include "opengl_util.hpp"
#include "SDL2/SDL_opengl.h"

#include "aabb.hpp"


#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <cmath>

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
	sdl2::ImageLoader imgLoader(IMG_INIT_PNG);
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
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
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
	gl::Program program({
		{GL_VERTEX_SHADER, "../shaders/vertex.glsl"},
		{GL_FRAGMENT_SHADER, "../shaders/fragment.glsl"}
	});

	// vertex data
	GLfloat vertices[] = {
		0.5f,  0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f,
		-0.5f,  0.5f,
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

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)NULL);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	bool running = true;
	while(running){
		for(SDL_Event e : sdlEvents) {
			if(e.type == SDL_QUIT)
			running = false;
		}

		{
			GLfloat timeValue = SDL_GetTicks();
			GLfloat greenValue = (std::sin(timeValue * 0.001)) / 2;
			GLfloat redValue = (std::sin(timeValue * 0.0011)) / 2;
			GLfloat blueValue = (std::sin(timeValue * 0.0012)) / 2;
			GLint vertexColorLocation = glGetUniformLocation(program.id, "ourColour");
			glUseProgram(program.id);
			glUniform3f(vertexColorLocation, redValue, greenValue, blueValue);
		}
		// render

		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//Update screen
		SDL_GL_SwapWindow( window.pointer );
	}
	return 0;
}
bool testAABB()
{
	typedef aabb::AABB<float, 2> Rect;
	Rect a{{
		{0, 1},
		{0, 1}
	}};
	Rect b = a;
	return aabb::intersect(a, b);
}
int main(int argc, char** args)
{

	try {
		run();
	} catch(const std::exception & e) {
		std::cout << e.what() << '\n';
	}
	return 0;
}
