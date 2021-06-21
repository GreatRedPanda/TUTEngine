#include "PropertiesTab.h"

void PropertiesTab::Update()
{

    ImGui::SetNextWindowPos(ImVec2(ScaleX * posX, ScaleY * posY));
    ImGui::Begin("Properties", &isOpen, flags);
    ImGui::SetWindowSize(ImVec2(ScaleX * sizeX, ScaleY * sizeY));
    ImGui::End();
}
