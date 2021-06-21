#pragma once
#ifndef  INPUT_H
#define INPUT_H


#include <glm.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Input
{
	GLFWwindow* my_window;
	double lastX ;
	double lastY ;
	double newX;
	double newY;
	bool firstMouse = true;
	GLFWcursorposfun mouseCallback;

	float lastFrame = 0;
	bool mouseInput = false;
	void	update();
	void key_pressed(GLFWwindow* window);
	static void mouseBtn_callback(GLFWwindow* window, int n, int k, int c);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void drop_callback(GLFWwindow* window, int n, const char ** c);
public:
	static Input *WindowInput;
	Input(GLFWwindow& window);
	glm::vec2  getMouseDelta();
	int  getMouseBtnState(int key);
	int  getKeyState(int key);
	void Update();
};
#endif // ! INPUT

