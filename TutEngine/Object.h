#pragma once
#ifndef  OBJECT_H
#define OBJECT_H


class Object
{
	typedef void (Object::*objThread)();
//o
protected:	
	objThread testThread;
public:	
	
	virtual void Update();
	virtual	void EditorUpdate();
	// void StartThread();
};

#endif // ! OBJECT