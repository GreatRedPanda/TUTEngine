#include "Transform.h"



void Transform::move(vec3 translation)
{
	position += translation;
	modelMatrix = glm::translate(modelMatrix, position);
}

void Transform::rotate(vec3 translation)
{
	angles += translation;
	
}

void Transform::Update()
{
}

void Transform::EditorUpdate()
{
}
