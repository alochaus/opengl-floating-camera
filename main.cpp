#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>
#ifndef DEBUG
#define ASSERT(x)
#define GLCall(x) x;
#else
#define ASSERT(x) if(!(x)) std::cin.get();
#define GLCall(x) GLClearError();\
                  x;\
                  ASSERT(GLLogCall(#x, __FILE__, __LINE__));
#endif

struct ShaderSource
{
	std::string vertexshader;
	std::string fragmentshader;
};

void GLClearError();
bool GLLogCall(const char* function, const char* filename, const unsigned short line);
void ProcessInput(GLFWwindow *window);
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
ShaderSource ParseShader(const std::string& filepath);
unsigned int CompileShader(const unsigned int type, const std::string& source);
unsigned int LinkProgram(const unsigned int vertexshader, const unsigned int fragmentshader);

const unsigned short W_WIDTH  = 800;
const unsigned short W_HEIGHT = 600;
const char*          W_TITLE  = "opengl window";

int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __MACOS__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(
		W_WIDTH,
		W_HEIGHT,
		W_TITLE,
		NULL,
		NULL
	);

	if(window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	ShaderSource src = ParseShader("uniform.shader");
	unsigned int vertexshader = CompileShader(GL_VERTEX_SHADER, src.vertexshader);
	unsigned int fragmentshader = CompileShader(GL_FRAGMENT_SHADER, src.fragmentshader);
	unsigned int shaderprogram = LinkProgram(vertexshader, fragmentshader);
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	float vertices[12] = {
		 0.5f,  0.5f,  0.0f,  // top right
		 0.5f, -0.5f,  0.0f,  // bottom right
		-0.5f, -0.5f,  0.0f,  // bottom left
		-0.5f,  0.5f,  0.0f   // top left
	};

	unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(VAO);

	glUseProgram(shaderprogram);

	while(!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(
			0xAA / 255.0, //R
			0x00 / 255.0, //G
			0xDD / 255.0, //B
			0xFF / 255.0  //A
		);
		glClear(GL_COLOR_BUFFER_BIT);

		int vertexcolorloaction = glGetUniformLocation(shaderprogram, "ourColor");
		float timevalue = glfwGetTime();
		float red = sin(timevalue);
		float blue = cos(timevalue);
		float green = tan(timevalue);
		glUniform4f(vertexcolorloaction, red, green, blue, 1.0f);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


ShaderSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	
	ShaderType type = ShaderType::NONE;

	while(getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if(line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << std::endl;
		}
	}

	return {ss[0].str(), ss[1].str()};
}

unsigned int CompileShader(const unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	return shader;
}

unsigned int LinkProgram(const unsigned int vertexshader, const unsigned int fragmentshader)
{
	int shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	int success;
	char infoLog[512];

	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
	}

	return shaderprogram;
}

void GLClearError()
{
	while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* filename, const unsigned short line)
{
	while(GLenum error = glGetError())
	{
		std::string errorname;
		std::string errordesc;
		switch(error)
		{
			case 0x0500:
				errorname = "GL_INVALID_ENUM";
				errordesc = "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			case 0x0501:
				errorname = "GL_INVALID_VALUE";
				errordesc = "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			case 0x0503:
				errorname = "GL_INVALID_OPERATION";
				errordesc = "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			case 0x0506:
				errorname = "GL_INVALID_FRAMEBUFFER_OPERATION";
				errordesc = "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			case 0x0505:
				errorname = "GL_OUT_OF_MEMORY";
				errordesc = "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
				break;
			default:
				errorname = std::to_string(error);
				errordesc = "";
		}

		std::cout 
		<< "[OpenGL Error]" << std::endl
		<< "File:\t" << filename << std::endl
		<< line << ":\t" << function << std::endl
		<< errorname << std::endl
		<< errordesc << std::endl;
		return false; //GL_NO_ERROR = 0
	}
	return true;
}
