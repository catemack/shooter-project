#include <effect.hpp>

Effect::Effect() :
	vertex(NULL),
	fragment(NULL),
	program(NULL)
{
}

Effect::~Effect()
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

bool Effect::init(const char* vsPath, const char* fsPath)
{
	// open shader files
	std::ifstream vsInStream(vsPath);
	std::ifstream fsInStream(fsPath);

	if (!vsInStream.good())
	{
		fprintf(stderr, "Failed to load vertex shader file %s", vsPath);
		return false;
	}
	if (!fsInStream.good())
	{
		fprintf(stderr, "Failed to load fragment shader file %s", fsPath);
		return false;
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
		return false;
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
		return false;
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
		return false;
	}

	return true;
}
