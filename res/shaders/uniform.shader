#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;

void main()
{
	gl_Position = aPos;
}

#shader fragment
#version 330 core

out vec4 FragColor;
uniform vec4 ourColor;

void main()
{
	FragColor = ourColor;
}
