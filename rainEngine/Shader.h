#pragma once
#include<string>

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

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

