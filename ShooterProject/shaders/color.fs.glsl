#version 330

// From vertex shader
in vec4 vcolor;
//in vec3 vpos;

// Application data
//uniform sampler3D sampler0;
//uniform vec3 fcolor;

// Output
out vec4 color;

void main()
{
	color = vcolor;
}
