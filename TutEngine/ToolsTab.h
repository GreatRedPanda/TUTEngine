#pragma once
#include "EditorTab.h"
class ToolsTab : public EditorTab
{
public:
	ToolsTab(float posX, float posY, float width, float height) :EditorTab(posX, posY, width, height)
	{}

	void Update() override;
};

