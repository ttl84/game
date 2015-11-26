// Wrapper for SDL.
// Uses destructor to clean-up so you don't have to.
#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <exception>

#include "image.hpp"
namespace sdl2{
	class Exception : public std::exception{
		std::string msg;

	public:
		explicit Exception(char const * s) : msg(s){}
		explicit Exception(std::string const & s) :msg(s){}

		virtual char const * what() noexcept
		{
			return msg.c_str();
		}
	};


	class SDL{
		bool good;
	public:
		SDL()
		{
			int result = SDL_Init(0);
			if(0 != result) {
				good = false;
				throw Exception(std::string("failed to initialize sdl: ") + SDL_GetError());
			} else {
				good = true;
			}
		}

		~SDL()
		{
			if(good) {
				SDL_Quit();
			}
		}
		bool isInitialized() const
		{
			return good;
		}
	};

	class VideoSystem {
		bool good;
	public:
		VideoSystem()
		{
			int result = SDL_InitSubSystem(SDL_INIT_VIDEO);
			if(0 != result) {
				good = false;
				throw Exception(std::string("failed to initialize sdl video: ") + SDL_GetError());
			} else {
				good = true;
			}
		}

		~VideoSystem()
		{
			if(good) {
				SDL_QuitSubSystem(SDL_INIT_VIDEO);
			}
		}

		bool isInitialized() const
		{
			return good;
		}
	};



	class Surface{
		SDL_Surface * ptr;
	public:
		SDL_Surface * getPtr() const
		{
			return ptr;
		}

		Surface(SDL_Surface* surface)
			:ptr(surface)
		{

		}
		~Surface()
		{
			if(ptr != NULL) {
				SDL_FreeSurface(ptr);
			}
		}
	};

	class ImageLoader {
		int initFlags;
		int resultFlags;
	public:
		ImageLoader(int args)
		{
			resultFlags = 0;
			quit();
			initFlags = args;
			resultFlags = IMG_Init(initFlags);
		}

		~ImageLoader()
		{
			quit();
		}

		Image loadRGBA(std::string filepath)
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

		bool isInitialized() const
		{
			return initFlags == resultFlags;
		}
		// Quits any initialized modules and resets initialization data.
		void quit()
		{
			initFlags = 0;
			if(resultFlags != 0) {
				IMG_Quit();
				resultFlags = 0;
			}
		}
	};

	struct Window {
		SDL_Window * pointer;

		Window(const char* title,
			int         x,
			int         y,
			int         w,
			int         h,
			Uint32      flags)
		{
			pointer = SDL_CreateWindow( title, x, y, w, h, flags);
			if(pointer == NULL) {
				throw Exception(std::string("failed to create sdl window: ") + SDL_GetError());
			}
		}
		~Window()
		{
			if(pointer != NULL) {
				SDL_DestroyWindow(pointer);
			}
		}
	};

	class GLContext {
		SDL_GLContext context;
	public:
		GLContext(Window& window)
		{
			context = SDL_GL_CreateContext(window.pointer);
			if(context == NULL) {
				throw Exception(std::string("failed to create opengl context: ") + SDL_GetError());
			}
		}

		~GLContext()
		{
			if(context != NULL) {
				SDL_GL_DeleteContext(context);
			}
		}

		SDL_GLContext get()
		{
			return context;
		}
	};

	class EventIterator {
		bool isEnd;
		SDL_Event event;
	public:
		EventIterator(bool endness)
		{
			isEnd = endness;
		}
		bool operator==(EventIterator const & other)
		{
			return isEnd && other.isEnd;
		}
		bool operator!=(EventIterator const & other)
		{
			return !(*this == other);
		}
		EventIterator & operator++()
		{
			if(!SDL_PollEvent(&event)) {
				isEnd = true;
			}
			return *this;
		}
		SDL_Event operator*() const
		{
			return event;
		}
	};
	class EventSystem {
	public:
		EventSystem()
		{
			int result = SDL_InitSubSystem(SDL_INIT_EVENTS);
			if(result != 0) {
				throw Exception(std::string("failed to initialize sdl event system") + SDL_GetError());
			}
		}
		~EventSystem()
		{
			SDL_QuitSubSystem(SDL_INIT_EVENTS);
		}

		EventIterator begin()
		{
			EventIterator iter(false);
			return ++iter;
		}
		EventIterator end()
		{
			return EventIterator(true);
		}
	};

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
} // end namespace sdl2

#endif
