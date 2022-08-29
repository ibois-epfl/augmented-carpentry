#version 330 core

// Output data
out vec4 color;
in vec4 color_from_vshader;

void main()
{
	// Output color = red
	color = color_from_vshader;
}
