#pragma once

// stdlib
#include <fstream>
#include <sstream>

#include <common.hpp>

class Shader
{
public:
	Shader(const std::string& vsShadvsPatherPath, const std::string&);
	~Shader();

	void use();

	void setFloat(const std::string& variable, const float value) const;
	void setVec3(const std::string& variable, const glm::vec3& value) const;
	void setVec4(const std::string& variable, const glm::vec4& value) const;
	void setMat3(const std::string& variable, const glm::mat4& value) const;
	void setMat4(const std::string& variable, const glm::mat4& value) const;

	GLuint program;

private:
	GLuint vertex;
	GLuint fragment;
};
