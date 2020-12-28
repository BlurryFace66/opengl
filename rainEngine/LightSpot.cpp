#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
	position(_position),
	angles(_angles),
	color(_color)
{
	UpdataDirection();
}

void LightSpot::UpdataDirection()
{
	direction = glm::vec3(0.0f, 0.0f, 1.0f); //��ʼ����ָ��z��
	direction = glm::rotateZ(direction, angles.z);   //��unity������תz����תx�����תy
	direction = glm::rotateX(direction, angles.x);   //��unity������תz����תx�����תy
	direction = glm::rotateY(direction, angles.y);   //��unity������תz����תx�����תy
	direction = -1.0f*direction;  //��Ϊ�����Ƿ���⣬���Է���Ҫ���ϸ�һ
}
