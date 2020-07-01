#ifndef DISPLAY_H
#define DISPLAY_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Display
{
	public:
		Display(const unsigned short WIDTH, const unsigned short HEIGHT, const char* W_TITLE);
		~Display();

		GLFWwindow* get_window() const;

		void swap_buffers();
		void poll_event();
		bool is_open();

	protected:
	private:
		GLFWwindow* window;
};


#endif
