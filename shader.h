#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<glad/glad.h>

class Shader
{
	public:
		Shader(const std::string& filename);
		~Shader();

		void Bind();
		
	protected:

	private:
		static const unsigned int _NUM_OF_SHADERS = 2;
		GLuint _program;
		GLuint _shaders[];
};

#endif
