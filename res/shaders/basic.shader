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

void main()
{
	FragColor = vec4(0.2f, 0.4f, 0.6f, 1.0f);
}

