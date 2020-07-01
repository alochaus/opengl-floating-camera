#include"diplay.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void initialize_and_configure_glfw();
void create_window(GLFWwindow* window, const unsigned short WIDTH, const unsigned short HEIGHT, const char* TITLE);
void initialize_glad();
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

Display::Display(const unsigned short WIDTH, const unsigned short HEIGHT, const char* TITLE)
{
	initialize_and_configure_glfw();
	
	window = glfwCreateWindow(
		WIDTH,
		HEIGHT,
		TITLE,
		NULL,
		NULL
	);

	if(window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	initialize_glad();
}

Display::~Display()
{
	
}

GLFWwindow* Display::get_window() const
{
	return window;
}

void Display::swap_buffers()
{
	glfwSwapBuffers(window);
}

void Display::poll_event()
{
	glfwPollEvents();
}

bool Display::is_open()
{
	return !glfwWindowShouldClose(window);
}

void initialize_and_configure_glfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __MACOS__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void initialize_glad()
{
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
