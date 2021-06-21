#pragma once
#include "StageObject.h"
#include "Component.h"
//typedef  class StageObject m_StageObject;

class StageComponent: public Component
{
protected:
	StageObject& stageParent;
public:
	StageComponent(Object& objectParent) :Component(objectParent), 
		stageParent(dynamic_cast<StageObject&>(objectParent))
	{
	
	}
};

