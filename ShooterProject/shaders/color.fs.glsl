#version 400

// From vertex shader
//in vec3 vcolor;
//in vec3 vpos;

// Application data
//uniform sampler3D sampler0;
//uniform vec3 fcolor;

// Output
out vec4 color;

void main()
{
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
