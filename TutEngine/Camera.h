#pragma once
#include <glm.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include "Transform.h"
#include "StageObject.h"
class Camera:  public StageObject
{
	glm::mat4 projection = glm::mat4(1.0);

public:
	Camera() 
	{}
	/*Camera(  Transform& t):StageObject(t)
	{}*/
void	InitPerspective(float fov, float aspectRatio, float near, float far);
void	InitOrtho(float left, float right, float bottom, float top);
	glm::mat4 getView();
	glm::mat4 getProjection();

};

