#include "Input.h"
#include <iostream>

 Input* Input::WindowInput=nullptr;
Input::Input(GLFWwindow& window)
{
    lastX = 0;
    lastY = 0;
    WindowInput = this;
    my_window = &window;
    mouseCallback = mouse_callback;
    glfwSetCursorPosCallback(&window, mouseCallback);
    glfwSetDropCallback(&window, drop_callback);
   // glfwSetWindowFocusCallback(&window, mouseBtn_callback);
    glfwSetMouseButtonCallback(&window, mouseBtn_callback);
   // glfwSetMouseButtonCallback(&window, mouseBtn_callback)
    //glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
}

glm::vec2 Input::getMouseDelta()
{
    return glm::vec2(WindowInput->newX- WindowInput->lastX , -WindowInput->newY + WindowInput->lastY);
}

int Input::getKeyState(int key)
{
    return glfwGetKey(my_window, key);
}

void Input::Update()
{
    double nX = newX;
    double nY = newY;
    glfwGetCursorPos(my_window, &newX,&newY);
    lastX = nX;
    lastY = nY;

}
void Input::mouseBtn_callback(GLFWwindow* window, int n, int k, int c)
{
    WindowInput-> mouseInput = true;
    std::cout << "UN UNPUT" << window << "\n";
   /* DataDragNDrop::BeginDrag();*/
}
void  Input::key_pressed(GLFWwindow* window)
{
   /* float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame*/;
    //lastFrame = currentFrame;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
   // mainCamera.move(*window, deltaTime * 2.5f);
    
}
void Input::drop_callback(GLFWwindow* window, int n, const char** c)
{
    std::cout << c << std::endl;
    int i;
    for (i = 0; i < n; i++)
         std::cout << c[i] << std::endl;
    
    /* WindowInput-> mouseInput = true;
     if (WindowInput->firstMouse)
     {
         WindowInput->newX = xpos;
         WindowInput->newY = ypos;
         WindowInput->firstMouse = false;
     }
     WindowInput->lastX = WindowInput->newX;
     WindowInput->lastY =   WindowInput->newY;
     WindowInput->newX = xpos;
     WindowInput->newY = ypos;*/
     //  std::cout <<"UN UNPUT"<< WindowInput->newX -WindowInput->lastX << "   " << WindowInput->lastY - WindowInput->newY << "\n";






}

void Input:: mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (WindowInput->mouseInput)
    {
        
    }
   /* WindowInput-> mouseInput = true;
    if (WindowInput->firstMouse)
    {
        WindowInput->newX = xpos;
        WindowInput->newY = ypos;
        WindowInput->firstMouse = false;
    }
    WindowInput->lastX = WindowInput->newX;
    WindowInput->lastY =   WindowInput->newY;
    WindowInput->newX = xpos;
    WindowInput->newY = ypos;*/
  //  std::cout <<"UN UNPUT"<< WindowInput->newX -WindowInput->lastX << "   " << WindowInput->lastY - WindowInput->newY << "\n";


 
  


}


int   Input::getMouseBtnState(int button)
{

   return glfwGetMouseButton(my_window, button);

}