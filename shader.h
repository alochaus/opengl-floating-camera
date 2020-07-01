#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

struct ShaderSource
{
	std::string vertexshader;
	std::string fragmentshader;
};

class Shader
{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void use();
		unsigned int get_id();
		
		void set_int(const int, const char* name);
		void set_mat4(const glm::mat4 &mat, const char* name);

	protected:
	private:
		ShaderSource src;
		unsigned int id;

};

#endif
