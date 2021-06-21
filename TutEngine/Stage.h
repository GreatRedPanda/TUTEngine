#pragma once
#include "StageObject.h"
#include <map>
class Stage
{


	std::map<int, StageObject*> stageObjects = std::map<int, StageObject*>();
public:
	Stage();
	Stage(std::string path);


};

