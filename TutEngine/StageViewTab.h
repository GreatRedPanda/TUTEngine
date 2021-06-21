#pragma once
#include "EditorTab.h"
#include "Camera.h"
#include "StageRenderer.h"
#include "FreeLookCamera.h"
class StageViewTab: public EditorTab
{
protected:
	Camera *stageCamera;
	StageRenderer *stageRenderer;


public:
	StageViewTab(float posX, float posY, float width, float height) :EditorTab(posX, posY, width, height)
	{
	
		stageCamera = new Camera();
		stageCamera->InitPerspective(45, 1024 / 720.0f, 0.1f, 200.0f);
		stageRenderer = new StageRenderer(1024, 720);
		stageCamera->AddComponent<FreeLookCamera>();
	}

	void Update() override;
	void SetCurrentStage();
};

