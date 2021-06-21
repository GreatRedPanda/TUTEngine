#include "StageViewTab.h"

void StageViewTab::Update()
{
    stageCamera->EditorUpdate();
    stageRenderer->Render(*stageCamera, 1024, 720);
    ImTextureID  tex = (void*)(intptr_t)stageRenderer->bufferTexture.getTextureBinding();

    ImGui::SetNextWindowPos(ImVec2(ScaleX * posX, ScaleY * posY));
    ImGui::Begin("Stage", &isOpen, flags);
    ImGui::SetWindowSize(ImVec2(ScaleX * sizeX, ScaleY * sizeY));
  
    //bool pressed = ImGui::Button("2D/3D", ImVec2(30, 20));
    //if (pressed)
    //{
    //    //  is2D = !is2D;
    //      /*  if (is2D)
    //            cam.InitOrtho(-100, 800, 600, -100);
    //        else
    //            cam.InitPerspective(45,  actualWindowWidth/ (float)actualWindowHeight, 0.1f,100);*/
    //}
    //ImGui::SameLine(0, 2);
    //ImGui::Button("Walk", ImVec2(30, 20));
    ImGui::Image(tex, ImVec2(ScaleX * sizeX, ScaleY * sizeY));
    ImGui::End();
}
