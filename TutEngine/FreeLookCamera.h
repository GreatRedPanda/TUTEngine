#pragma once
#ifndef FREE_LOOK_H
#define FREE_LOOK_H
#include <glm.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include "StageComponent.h"
#include "Input.h"
#include "StageObject.h"
class FreeLookCamera : public StageComponent
{
	float lastMouseX;
	float lastMouseY;
	float yaw;
	float pitch;
	bool firstMove;
	float lastFrame;
	void	move();
	void	rotate();
public:
	FreeLookCamera(Object& objectParent) :StageComponent(objectParent)
	{
		yaw = 0;
		pitch = 0;
		firstMove = true;
		lastMouseX = 0;
		lastMouseY = 0;
	}
	void Update() override;
	void EditorUpdate() override;

	glm::vec3 FRONT;
};
#endif