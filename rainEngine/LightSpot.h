#pragma once
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightSpot
{
public:
	glm::vec3 position;   
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 color;
	float cosPhyInner=0.9;
	float cosPhyOutter=0.85;

	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));

	void UpdataDirection();
};

