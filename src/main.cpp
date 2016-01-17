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

	RealQuadID id1 = quads.addVertex(quad1);
	IndexedQuadID iid1 = quads.addIndex(id1);
	IndexedQuadID iid2 = quads.addIndex(id1);


	quads.uploadIndices();
	quads.uploadVertices();

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
		quads.setupVertexFormat(0);
		quads.setupTextureCoordinateFormat(1);
		quads.setupTransformFormat(2);
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
		//trans = glm::translate(trans, glm::vec3(x, y, 0));
		//trans = glm::rotate(trans, angle, glm::vec3(0, 0, 1.0));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glm::mat4 & trans1 = quads.transform(iid1);
		trans1 = glm::mat4();
		trans1 = glm::translate(trans1, glm::vec3(x, y, 0));
		trans1 = glm::rotate(trans1, angle, glm::vec3(0, 0, 1.0));

		// reupload transform data
		quads.uploadTransforms();


		// render
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
			// same as glDrawElements, but with an extra parameter stating
			// how many instances to draw
			quads.draw();
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
