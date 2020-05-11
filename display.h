#ifndef DISPLAY_H
#define DISPLAY_H
#include<string>
#include<SDL2/SDL.h>

class Display
{
	public:
		Display(const std::string& title, const short width, const short height);
		void SwapBuffers();
		bool IsClosed();
		void Update();
		void Clear(float r, float g, float b, float a);
		~Display();
	protected:

	private:
		SDL_Window* _window;
		SDL_GLContext _context;
		bool _IsClosed;
};

#endif
