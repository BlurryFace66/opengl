#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
	position(_position),
	angles(_angles),
	color(_color)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
	UpdataDirection();
}

void LightSpot::UpdataDirection()
{
	direction = glm::vec3(0.0f, 0.0f, 1.0f); //初始化，指向z轴
	direction = glm::rotateZ(direction, angles.z);   //在unity中是先转z，再转x，最后转y
	direction = glm::rotateX(direction, angles.x);   //在unity中是先转z，再转x，最后转y
	direction = glm::rotateY(direction, angles.y);   //在unity中是先转z，再转x，最后转y
	direction = -1.0f*direction;  //因为物体是反射光，所以方向要乘上负一
}
