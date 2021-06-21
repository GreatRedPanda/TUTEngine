#pragma once
#include<iostream>
#include <imgui.h>


//#include<GL/glew.h>
#include<glm.hpp>
#include<gtc/matrix_inverse.hpp>
//#include<GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "DragNDropManager.h"
class EditorTab
{
protected:
	float sizeX;
	float sizeY;
	float posX;
	float posY;
	bool isOpen;
	ImGuiWindowFlags flags;
	void setPosition();
public: 

	EditorTab(float posX, float posY, float width, float height)
	{
		flags = 0;
		flags |= ImGuiWindowFlags_::ImGuiWindowFlags_NoMove;
		flags |= ImGuiWindowFlags_::ImGuiWindowFlags_NoResize;
		sizeX = width;
		this->posX = posX;
		this->posY = posY;
		sizeY = height;
		isOpen = false;
	}
	
	virtual	void Update()=0 ;

	static float ScaleX;
	static float ScaleY;
};

