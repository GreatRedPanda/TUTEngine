#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include "Component.h"
using namespace glm;
class Transform: public Component
{
public:
	Transform(Object& objectParent) :Component(objectParent)
	{
		angles = vec3(0, 0, 0);
		position = vec3(0,0, 0);
		up = vec3(0, 1, 0);
		front = vec3(0, 0, -1);
		right = vec3(1, 0, 0);
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
	
	}
	vec3 up;
	vec3 right;
	vec3 front;
	vec3 position;
	mat4 modelMatrix;
	//X -pitch, Y -yaw, Z-roll
	vec3 angles;

	void move(vec3 translation);
	void rotate(vec3 translation);

	void Update() ;
	void EditorUpdate() ;
};

#endif