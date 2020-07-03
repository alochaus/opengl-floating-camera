#include"shader.h"

static ShaderSource parse_shader(const std::string& filepath);
static unsigned int compile_shader(const unsigned int type, const std::string& source);
static unsigned int link_program(const unsigned int vertexshader, const unsigned int fragmentshader);

Shader::Shader(const std::string& filepath)
{
	src = parse_shader("res/shaders/projection.shader");
	unsigned int vertexshader = compile_shader(GL_VERTEX_SHADER, src.vertexshader);
	unsigned int fragmentshader = compile_shader(GL_FRAGMENT_SHADER, src.fragmentshader);
	id = link_program(vertexshader, fragmentshader);
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}

Shader::~Shader()
{

}

void Shader::use()
{
	glUseProgram(id);
}

unsigned int Shader::get_id()
{
	return id;
}

void Shader::set_int(const int num, const char* name)
{
	glUniform1i(glGetUniformLocation(id, name), num);
}
void Shader::set_mat4(const glm::mat4 &mat, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}

static ShaderSource parse_shader(const std::string& filepath)
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

static unsigned int compile_shader(const unsigned int type, const std::string& source)
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

static unsigned int link_program(const unsigned int vertexshader, const unsigned int fragmentshader)
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
