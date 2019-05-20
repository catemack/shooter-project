#version 400

// Input
layout (location = 0) in vec3 in_position;
//in vec3 in_color;

// Output
//out vec3 vcolor;
//out vec3 vpos;

// Application data
//uniform mat3 transform;
//uniform mat3 projection;

void main()
{
	//vpos = in_position;
	//vcolor = in_color;
	//vec3 pos = projection * transform * in_position;
	//gl_Position = vec4(pos, 1.0);
	gl_Position = vec4(in_position, 1.0f);
}
