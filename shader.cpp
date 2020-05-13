#include"shader.h"
#include<fstream>
#include<iostream>

static std::string LoadShader(const std::string& filename);
static void CheckShaderError(GLuint shader, GLuint flag, bool isprogram, const std::string& errormsg);
static GLuint CreateShader(const std::string& text, GLenum shadertype);

Shader::Shader(const std::string& filename)
{
	_program = glCreateProgram();
	_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < _NUM_OF_SHADERS; i++)
		glAttachShader(_program, _shaders[i]);

	glBindAttribLocation(_program, 0, "position");

	glLinkProgram(_program);
	CheckShaderError(_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(_program);
	CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
}

Shader::~Shader()
{
	for(unsigned int i = 0; i < _NUM_OF_SHADERS; i++)
	{
		glAttachShader(_program, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}
	glDeleteProgram(_program);
}

void Shader::Bind()
{
	glUseProgram(_program);
}

static std::string LoadShader(const std::string& filename)
{
	std::ifstream file;
	std::string   output;
	std::string   line;

	file.open((filename).c_str());
	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	} else {
		std::cerr << "Unable to load the shader: " << filename << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isprogram, const std::string& errormsg)
{
	GLint success = 0;
	GLchar error[0x400] = { 0 };

	if(isprogram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE)
	{
		if(isprogram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errormsg << ": '" << error <<"'" << std::endl;
	}
}

static GLuint CreateShader(const std::string& text, GLenum shadertype)
{
	GLuint shader = glCreateShader(shadertype);

	if(shader == 0)
		std::cerr << "Error: Shader creation failed." << std::endl;

	const GLchar* shdrsrcstrs[1];
	GLint shdrsrcstrlens[1];

	shdrsrcstrs[0] = text.c_str();
	shdrsrcstrlens[0] = text.length();
	
	glShaderSource(shader, 1, shdrsrcstrs, shdrsrcstrlens);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");
	return shader;
}

