#version 330

// Input
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

// Output
out vec4 vcolor;

// Application data
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vcolor = in_color;
	gl_Position = projection * view * transform * vec4(in_position, 1.0f);
}
