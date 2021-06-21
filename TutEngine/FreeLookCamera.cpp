#include "FreeLookCamera.h"
#include <iostream>
void FreeLookCamera::move()
{
    float currentFrame = glfwGetTime();
    float  deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float cameraSpeed = 2.5 * deltaTime;
    if (Input::WindowInput->getKeyState( GLFW_KEY_W) == GLFW_PRESS)
        stageParent.getTransform()->move( cameraSpeed * stageParent.getTransform()->front);
    if (Input::WindowInput->getKeyState(GLFW_KEY_S) == GLFW_PRESS)
        stageParent.getTransform()->move(-cameraSpeed * stageParent.getTransform()->front);


    if (Input::WindowInput->getKeyState(GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 t =  glm::cross(stageParent.getTransform()->front, stageParent.getTransform()->up);
        t = cameraSpeed * glm::normalize(t);
        stageParent.getTransform()->move(-t);
    }
    if (Input::WindowInput->getKeyState(GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 t = 
            glm::cross(stageParent.getTransform()->front, stageParent.getTransform()->up);
        t = cameraSpeed * glm::normalize(t);
        stageParent.getTransform()->move(t);
    }
}

void FreeLookCamera::rotate()
{
    
    int mouseBtn = Input::WindowInput->getMouseBtnState(GLFW_MOUSE_BUTTON_LEFT);
    if (mouseBtn != GLFW_PRESS)
        return;
    vec2 mouse = Input::WindowInput->getMouseDelta();
    if (firstMove)
    {
        firstMove = false;
        lastMouseX = mouse.x;
        lastMouseY = mouse.y;
    }
   
    float xoffset = mouse.x ;
    float yoffset =  mouse.y;
   /* if (abs(xoffset) < 0.1f || abs(xoffset) < 0.1f)
        return;*/
    lastMouseX = mouse.x;
    lastMouseY = mouse.y;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
 
    //x=pitch y=yaw z=roll
  /*  stageParent.getTransform()->rotate(vec3(yoffset, xoffset,0));*/
   
   // clamp pitch
    yaw += xoffset;
    pitch += yoffset;
   // std::cout << yaw << "   " << pitch << "\n";
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  FRONT = glm::normalize(direction);
  stageParent.getTransform()->front = FRONT;
  //stageParent.getTransform()->front.x = direction.y;
  //stageParent.getTransform()->front.y = direction.z;
  //stageParent.getTransform()->front.z = direction.x;
}


void FreeLookCamera::Update()
{
}

void FreeLookCamera::EditorUpdate()
{
    move();
    rotate();
}
