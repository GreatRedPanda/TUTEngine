#pragma once
#include "EditorTab.h"
class PropertiesTab : public EditorTab
{
public:
	PropertiesTab(float posX, float posY, float width, float height) :EditorTab(posX, posY, width, height)
	{}

	void Update() override;
};

