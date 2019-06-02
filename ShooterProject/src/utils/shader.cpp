#include "shader.hpp"

Shader::Shader(const std::string& vsPath, const std::string& fsPath) :
	vertex(NULL),
	fragment(NULL),
	program(NULL)
{
	// open shader files
	std::ifstream vsInStream(vsPath);
	std::ifstream fsInStream(fsPath);

	if (!vsInStream.good())
	{
		fprintf(stderr, "Failed to load vertex shader file %s", vsPath.c_str());
		return;
	}
	if (!fsInStream.good())
	{
		fprintf(stderr, "Failed to load fragment shader file %s", fsPath.c_str());
		return;
	}

	// read sources
	std::stringstream vsStringStream, fsStringStream;
	vsStringStream << vsInStream.rdbuf();
	fsStringStream << fsInStream.rdbuf();
	std::string vsString = vsStringStream.str();
	std::string fsString = fsStringStream.str();
	const char* vsSource = vsString.c_str();
	const char* fsSource = fsString.c_str();
	GLsizei vsLen = (GLsizei)vsString.size();
	GLsizei fsLen = (GLsizei)fsString.size();

	int success;
	char infoLog[512];

	// compile vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vsSource, &vsLen);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		fprintf(stderr, "Vertex shader compilation failed:\n%s", infoLog);
		return;
	}

	// compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fsSource, &fsLen);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		fprintf(stderr, "Fragment shader compilation failed:\n%s", infoLog);
		return;
	}

	// linking
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		fprintf(stderr, "Shader program linking failed:\n%s", infoLog);
		return;
	}
}

Shader::~Shader()
{
	if (program != NULL)
	{
		glDeleteProgram(program);
	}

	if (vertex != NULL)
	{
		glDeleteShader(vertex);

	}

	if (fragment != NULL)
	{
		glDeleteShader(fragment);
	}
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::setFloat(const std::string& variable, const float value) const
{
	glUniform1f(glGetUniformLocation(program, variable.c_str()), value);
}

void Shader::setVec3(const std::string& variable, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(program, variable.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& variable, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(program, variable.c_str()), 1, &value[0]);
}

void Shader::setMat3(const std::string& variable, const glm::mat4& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(program, variable.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string& variable, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(program, variable.c_str()), 1, GL_FALSE, &value[0][0]);
}
