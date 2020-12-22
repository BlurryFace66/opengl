#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void main1()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);// 初始化一个单位矩阵
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));// 将向量(1, 1, 0)与单位矩阵相乘
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
	
	while (true)
	{

	}
	return ;
}