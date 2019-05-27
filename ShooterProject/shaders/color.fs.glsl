#version 330

// From vertex shader
in vec4 vcolor;

// Output
out vec4 color;

void main()
{
	color = vcolor;
}
