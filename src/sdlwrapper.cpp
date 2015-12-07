#include "sdlwrapper.hpp"

namespace sdl2{
	Image ImageLoader::loadRGBA(std::string filepath)
	{
		Surface surf(IMG_Load(filepath.c_str()));
		if(surf.getPtr() == NULL) {
			return Image();
		}

		SDL_Surface * surface = surf.getPtr();
		SDL_PixelFormat * format = surface->format;

		Image img;
		img.width = surface->w;
		img.height = surface->h;
		img.bytesPerPixel = format->BytesPerPixel;

		if(img.bytesPerPixel == 4) {
			for(unsigned i = 0; i < img.width * img.height; i++) {
				Uint32 * pixels = (Uint32*)(surface->pixels);
				Uint8 r = 0, g = 0, b = 0, a = 0;
				SDL_GetRGBA(pixels[i], format, &r, &g, &b, &a);
				img.bytes.push_back(r);
				img.bytes.push_back(g);
				img.bytes.push_back(b);
				img.bytes.push_back(a);
			}
		} else {
			throw Exception("loadRGBA: unable to load image format");
		}
		return img;
	}

	int initGL()
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
} // end namespace
