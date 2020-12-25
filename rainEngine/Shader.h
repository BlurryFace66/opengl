#pragma once
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;     //用const char*保证后面的东西只能写入一次
	const char* fragmentSource;
	unsigned int ID;     //shader program ID

	void use();
	void SetUniform3f(const char* paramNameString, glm::vec3 param);
	void SetUniform1f(const char* paramNameString, float param);

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

