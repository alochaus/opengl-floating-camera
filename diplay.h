#ifndef DISPLAY_H
#define DISPLAY_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>

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
