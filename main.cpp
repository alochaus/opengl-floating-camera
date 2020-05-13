#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"display.h"
#include"shader.h"

const std::string W_TITLE     = "messingwithopengl";
const unsigned short W_WIDTH  = 800;
const unsigned short W_HEIGHT = 600;
const std::string SHADER_PATH = "./res/BasicShader";

int main()
{
	Display display(W_TITLE, W_WIDTH, W_HEIGHT);
	Shader shader(SHADER_PATH);

	while(!display.IsClosed())
	{
		display.Clear(0x00, 0x00, 0xFF, 0xFF);
		shader.Bind();
		display.Update();
	}

	return 0;
}
