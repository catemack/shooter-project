#version 330

// From vertex shader
in vec4 vcolor;

// Uniforms
uniform vec3 ambientLightColor;
uniform float ambientLightStrength;

// Output
out vec4 color;

void main()
{
	color = vcolor * vec4(ambientLightColor, 1.0) * ambientLightStrength;
}
