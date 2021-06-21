#pragma once
#ifndef  STAGE_OBJECT_H
#define STAGE_OBJECT_H


#include "Object.h"
#include "Transform.h"
#include <typeinfo>
#include "Component.h"
#include <map>
#include <string>
#include <thread>
#include <future>

#include <mutex>
typedef  class Component m_Component;
class StageObject: public Object
{

protected:
	std::future<void> *o_thread;

	std::map<std::string, m_Component*> objectComponents = std::map<std::string, m_Component*>();
public:
	StageObject() //:transform(objectTransform)
	{
		AddComponent<Transform>();
		//transform = &objectTrans
		//form;
	}
	Transform* getTransform()
	{
		m_Component* t = GetComponent<Transform>();
		Transform* res = dynamic_cast<Transform*>(t);
		return res;
	
	};
	template<typename T>	m_Component* GetComponent()
	{
		std::string  typeName = typeid(T).raw_name();
		m_Component* res = objectComponents[typeName];
		return res;
	}
	template<typename T> void AddComponent()
	{
		StageObject& refO2 = *this;
		T* t1 = new T(refO2);
		std::string  typeName = typeid(T).raw_name();
		objectComponents.insert(std::make_pair(typeName, t1));
	}
	void	 Update() override
	{
		for (auto& i : objectComponents)
		{
			i.second->Update();

		}

	}
	void EditorUpdate() override
	{
//
		//while (true)
		{
			for (auto& i : objectComponents)
			{
				i.second->EditorUpdate();

			}
			//o_thread->wait();
		//	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	void StartThread()
	{
		//testThread = EditorUpdate;
	//auto	 test_thread = std::async(std::launch::async , &StageObject::EditorUpdate, this);
		//test_thread.join();
	//o_thread = &test_thread;
	}
};

#endif // ! STAGE_OBJECT_H