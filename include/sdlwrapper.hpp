// Wrapper for SDL.
// Uses destructor to clean-up so you don't have to.
#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H
#include "SDL2/SDL.h"
#include <string>
namespace sdl2{
	class Exception {
		std::string msg;
		
	public:
		Exception(std::string const & s) :msg(s){}
		
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
	
	class Window {
		SDL_Window * window;
	public:
		Window(char const * name, unsigned width, unsigned height, unsigned flags)
		{
			window = SDL_CreateWindow( name,
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				width, height,
				flags );
			if(window == NULL) {
				throw Exception(std::string("failed to create sdl window: ") + SDL_GetError());
			}
		}
		~Window()
		{
			if(window != NULL) {
				SDL_DestroyWindow(window);
			}
		}
		SDL_Window* get()
		{
			return window;
		}
	};
	
	class GLContext {
		SDL_GLContext context;
	public:
		GLContext(Window& window)
		{
			context = SDL_GL_CreateContext( window.get() );
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
		operator==(EventIterator const & other)
		{
			return isEnd && other.isEnd;
		}
		operator!=(EventIterator const & other)
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
} // end namespace sdl2

#endif