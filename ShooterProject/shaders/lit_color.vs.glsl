#version 330

// Input
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec3 in_normal;

// Output
out vec4 vcolor;
out vec3 frag_pos;
out vec3 normal;

// Application data
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vcolor = in_color;
	frag_pos = vec3(transform * vec4(in_position, 1.0f));
	normal = in_normal;
	gl_Position = projection * view * transform * vec4(in_position, 1.0f);
}
