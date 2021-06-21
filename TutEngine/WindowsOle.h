#pragma once

class WindowsOle
{
	static  bool isInDragProcess ;
		void dragTask();
		void dragTest();
public:
	WindowsOle();

	~WindowsOle();
	
	void DragDocument();
	static WindowsOle* WindowsOleInstance;
};

