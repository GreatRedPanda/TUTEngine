#pragma once
#ifndef  COMPONENT_H
#define COMPONENT_H

#include "Object.h"
typedef  class Object o_Object;
class Component
{
	
protected:
	int ID;
	o_Object& parent;
public:

	/*Component()
	{}*/
	Component(o_Object& parentObject) :parent(parentObject)
	{}

	virtual void Update()=0;
	virtual	void EditorUpdate()=0;
};

#endif // ! COMPONENT