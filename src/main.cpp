#include "sdlwrapper.hpp"
#include "opengl_util.hpp"

#include "aabb.hpp"
#include "quads.hpp"

#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <cmath>


int run()
{
	unsigned win_w = 640;
	unsigned win_h = 640;
	sdl2::SDL sdl;
	sdl2::VideoSystem sdlVideo;
	sdl2::ImageLoader imgLoader(IMG_INIT_PNG);
	sdl2::EventSystem sdlEvents;

	int result = sdl2::initGL();
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
	Quads quads;
	Quad quad1{
		Vertex3{{0.5,  0.5, 0}, {1, 1}},
		Vertex3{{0.5, -0.5, 0}, {1, 0}},
		Vertex3{{-0.5, -0.5, 0}, {0, 0}},
		Vertex3{{-0.5,  0.5, 0}, {0, 1}}
	};
	Quad quad2 = {
		Vertex3{{0.7,  0.5, 0}, {1, 1}},
		Vertex3{{0.7, -0.5, 0}, {1, 0}},
		Vertex3{{-0.1, -0.5, 0}, {0, 0}},
		Vertex3{{-0.1,  0.5, 0}, {0, 1}}
	};
	RealQuadID id1 = quads.addVertex(quad1);
	RealQuadID id2 = quads.addVertex(quad2);
	quads.addIndex(id1);
	quads.addIndex(id2);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(
			GL_ARRAY_BUFFER,
			quads.vertexDataByteCount(),
			quads.vertexData(),
			GL_STATIC_DRAW);

		// vertex coordinates
		glVertexAttribPointer(
			0,
			Quads::VertexType::PositionComponents,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Quads::VertexType),
			(GLvoid*)0
		);
		glEnableVertexAttribArray(0);

		// texture coordinates
		glVertexAttribPointer(
			1,
			Quads::VertexType::TextureComponents,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Quads::VertexType),
			(GLvoid*) offsetof(Quads::VertexType, texture)
		);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			quads.indexDataByteCount(),
			quads.indexData(),
			GL_STATIC_DRAW);

	glBindVertexArray(0);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
		Image image = imgLoader.loadRGBA("../img/drawing.png");
		flipVertically(image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			image.getWidth(), image.getHeight(),
			0, GL_RGBA, GL_UNSIGNED_BYTE, image.ptr(0, 0, 0));
		glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glUseProgram(program.id);



	GLuint transformLoc = glGetUniformLocation(program.id, "transform");

	float x = 0, y = 0, angle = 0;
	bool moveLeft = false, moveRight = false, moveUp = false, moveDown = false;
	bool turnLeft = false, turnRight = false;

	bool running = true;
	while(running){
		for(SDL_Event e : sdlEvents) {
			if(e.type == SDL_QUIT) {
				running = false;
			} else if(e.type == SDL_KEYDOWN) {
				if(e.key.keysym.sym == SDLK_LEFT) {
					moveLeft = true;
				} else if(e.key.keysym.sym == SDLK_RIGHT) {
					moveRight = true;
				} else if(e.key.keysym.sym == SDLK_UP) {
					moveUp = true;
				} else if(e.key.keysym.sym == SDLK_DOWN) {
					moveDown = true;
				} else if(e.key.keysym.sym == SDLK_a) {
					turnLeft = true;
				} else if(e.key.keysym.sym == SDLK_d) {
					turnRight = true;
				}
			} else if(e.type == SDL_KEYUP) {
				if(e.key.keysym.sym == SDLK_LEFT) {
					moveLeft = false;
				} else if(e.key.keysym.sym == SDLK_RIGHT) {
					moveRight = false;
				} else if(e.key.keysym.sym == SDLK_UP) {
					moveUp = false;
				} else if(e.key.keysym.sym == SDLK_DOWN) {
					moveDown = false;
				} else if(e.key.keysym.sym == SDLK_a) {
					turnLeft = false;
				} else if(e.key.keysym.sym == SDLK_d) {
					turnRight = false;
				}
			}
		}

		if(moveLeft) {
			x -= 0.01;
		}

		if(moveRight) {
			x += 0.01;
		}

		if(moveUp) {
			y += 0.01;
		}

		if(moveDown) {
			y -= 0.01;
		}

		if(turnLeft) {
			angle += 0.01;
		}

		if(turnRight) {
			angle -= 0.01;
		}

		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(x, y, 0));
		trans = glm::rotate(trans, angle, glm::vec3(0, 0, 1.0));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		// render

		glClear(GL_COLOR_BUFFER_BIT);



		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, quads.indexDataCount(), Quads::IndexTypeID, 0);
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
