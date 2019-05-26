#version 330

// Input
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

// Output
out vec4 vcolor;
//out vec3 vpos;

// Application data
uniform mat4 transform;
//uniform mat3 projection;

void main()
{
	vcolor = in_color;
	gl_Position = transform * vec4(in_position, 1.0f);
}
