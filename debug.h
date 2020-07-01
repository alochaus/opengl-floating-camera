#ifndef DEBUG_H
#define DEBUG_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>

#ifndef DEBUG
#define ASSERT(x)
#define GLCall(x) x;
#else
#define ASSERT(x) if(!(x)) std::cin.get();
#define GLCall(x) GLClearError();\
                  x;\
                  ASSERT(GLLogCall(#x, __FILE__, __LINE__));
#endif

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

#endif
