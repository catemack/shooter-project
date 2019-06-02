#version 330

// From vertex shader
in vec4 vcolor;
in vec3 frag_pos;
in vec3 normal;

// Uniforms
uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 ambient_light_color;
uniform float ambient_light_strength;
uniform mat3 normal_mat;
uniform vec3 view_pos;

// Output
out vec4 color;

void main()
{
	// ambient lighting
	vec3 ambient = ambient_light_color * ambient_light_strength;

	// diffuse lighting
	vec3 norm = normalize(normal * normal_mat);
	vec3 light_dir = normalize(light_pos - frag_pos);
	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = diff * light_color;

	// specular lighting
	float specular_strength = 0.5;
	vec3 view_dir = normalize(view_pos - frag_pos);
	vec3 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 64);
	vec3 specular = specular_strength * spec * light_color;

	color = vcolor * vec4(ambient + diffuse + specular, 1.0);
}
