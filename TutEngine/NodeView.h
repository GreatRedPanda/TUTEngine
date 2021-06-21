#pragma once
#include "imgui.h"
#include "Node.h"
class NodeView
{

	Node* nodeSource;
public:
	 NodeView(Node& node);
	void Update();
};

