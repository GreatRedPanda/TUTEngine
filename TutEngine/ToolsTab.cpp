#include "ToolsTab.h"

void ToolsTab::Update()
{
    ImGui::SetNextWindowPos(ImVec2(ScaleX * posX, ScaleY * posY));
    ImGui::Begin("Tools", &isOpen, flags);
    ImGui::SetWindowSize(ImVec2(ScaleX * sizeX, ScaleY * sizeY));
    ImGui::End();
}
