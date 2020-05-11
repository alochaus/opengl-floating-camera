#include"display.h"
#include<iostream>
#include<glad/glad.h>

/*
 * PUBLIC
 */

Display::Display(const std::string& title, const short width, const short height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	_context = SDL_GL_CreateContext(_window);

	if(!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		this->~Display();
	}

	_IsClosed = false;
}

Display::~Display()
{
	SDL_GL_DeleteContext(_window);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Display::SwapBuffers()
{
	SDL_GL_SwapWindow(_window);
}

bool Display::IsClosed()
{
	return _IsClosed;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r / 255.0f,
	             g / 255.0f,
	             b / 255.0f,
	             a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update()
{
	SDL_GL_SwapWindow(_window);
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			_IsClosed = true;
	}
}
