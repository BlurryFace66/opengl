#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void main1()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);// ��ʼ��һ����λ����
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));// ������(1, 1, 0)�뵥λ�������
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
	
	while (true)
	{

	}
	return ;
}