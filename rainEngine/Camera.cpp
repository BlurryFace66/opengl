#include "Camera.h"

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)  //目标点版本
{
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) //欧拉角版本
{
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY*SenseX;
	Yaw -= deltaX * SenseY;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPos()
{
	Position += Forward * speedZ;
	Position += Right * speedX;
}

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}