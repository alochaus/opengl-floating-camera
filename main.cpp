#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// the maximum value for an unsigned 2 byte integer is 65,535 so we're safe
const unsigned short W_WIDTH  = 800;
const unsigned short W_HEIGHT = 600;
const std::string    W_TITLE  = "OpenGL Window";

int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	
	GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, W_TITLE.c_str(), NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0xEB / 255.0f,
		             0x00 / 255.0f,
		             0x00 / 255.0f,
		             0xFF / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
