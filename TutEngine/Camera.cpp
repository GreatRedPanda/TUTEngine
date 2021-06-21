#include "Camera.h"



void Camera::InitPerspective(float fov, float aspectRatio, float near, float far)
{
	projection = glm::perspective(fov, aspectRatio, near, far);
}

 void Camera::InitOrtho(float left, float right, float bottom, float top)
{
	projection = glm::ortho(-0.0f, 100.0f, 0.0f, 100.0f, -10.0f,10.0f);
}

 glm::mat4 Camera::getView()
 {
	 glm::vec3 front = getTransform()->front;
	//Transform *t= transform;
	return   glm::lookAt(getTransform()->position, getTransform()->position + getTransform()->front, getTransform()->up);
	 //return glm::mat4(1);
 }

glm::mat4 Camera::getProjection()
{
	return projection;
}
