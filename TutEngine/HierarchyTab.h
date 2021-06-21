#pragma once
#include "EditorTab.h"
class HierarchyTab : public EditorTab
{

public:
	HierarchyTab(float posX, float posY, float width, float height) :EditorTab(posX, posY, width, height)
	{
	
	//	ImGui::SetNextWindowPos(ImVec2(ScaleX * posX, ScaleY * posY));
		//ImGui::Begin("Hierarchy");
		//, &isOpen, flags
	//	ImGui::SetWindowSize(ImVec2(ScaleX * sizeX, ScaleY * sizeY));
	
	}

	void Update() override;
};

