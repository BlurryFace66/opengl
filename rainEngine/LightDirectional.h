#pragma once
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightDirectional
{
public:
	glm::vec3 position;   //平行光的位置其实是没用的，不影响光照效果
	glm::vec3 angles;
	glm::vec3 direction=glm::vec3(0.0f,0.0f,1.0f);
	glm::vec3 color;

	LightDirectional(glm::vec3 _position,glm::vec3 _angles,glm::vec3 _color=glm::vec3(1.0f,1.0f,1.0f));

	void UpdataDirection();
};

