#version 330

// Input attributes
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texcoord;

// Passed to fragment shader
out vec2 texcoord;

// Application data
uniform mat4 transform;
//uniform mat3 projection;

void main()
{
	texcoord = in_texcoord;
	gl_Position = transform * vec4(in_position, 1.0);
}
