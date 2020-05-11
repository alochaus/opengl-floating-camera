#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"display.h"

const std::string W_TITLE = "messingwithopengl";
const short W_WIDTH       = 800;
const short W_HEIGHT      = 600;

int main()
{
	Display display(W_TITLE, W_WIDTH, W_HEIGHT);
	
	while(!display.IsClosed())
	{
		display.Clear(0x00, 0x00, 0xFF, 0xFF);
		display.Update();
	}

	return 0;
}
