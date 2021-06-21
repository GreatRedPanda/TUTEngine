#include "EditorTab.h"
float EditorTab::ScaleX = 1;
float EditorTab::ScaleY = 1;

void EditorTab::setPosition()
{
    ImGui::SetNextWindowPos(ImVec2(posX * ScaleX, posY * ScaleY));
    ImGui::Begin("Stage", &isOpen, flags);
    ImGui::SetWindowSize(ImVec2(ScaleX *sizeX, ScaleY *sizeY));
}
