#pragma once
#include "EditorTab.h"
#include "AssetsDatabase.h"

class ProjectTab : public EditorTab
{
	AssetsDatabase* currentAssets;
	void drawDirectory(Asset *directoryAsset);
public:
	ProjectTab(AssetsDatabase & projectAssets, float posX, float posY, float width, float height) :EditorTab(posX, posY, width, height)
	{
		currentAssets = &projectAssets;
	}
	void Update() override;
	
};